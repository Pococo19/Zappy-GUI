/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ModelLoader.cpp
*/

#include <ZapGUI/Drawable/ModelBase.hpp>
#include <ZapGUI/Filename.hpp>

#include <filesystem>
#include <unordered_map>

static std::string _find_texture_file(const std::string &texture_name, const std::string &texture_directory)
{
    if (texture_directory.empty()) {
        return texture_name;
    }

    const std::string filename = zap::Filename::extract(texture_name);
    const std::string full_path = texture_directory + "/" + filename;

    /** @brief check if file exists */
    if (zap::Filename::exists(full_path)) {
        return full_path;
    }

    /** @brief if not found, check with the original pathname */
    if (zap::Filename::exists(texture_name)) {
        return texture_name;
    }

    return "";
}

/**
* lambda parsers workers
*
* @brief mtl is a material template library
*/

static const auto _mtl_filename_worker = [](const std::string &line, std::string &result) {
    std::istringstream iss(line);
    std::string command;

    iss >> command;
    if (command == "mtllib") {
        std::string mtl_filename;

        iss >> mtl_filename;
        result = mtl_filename;
    }
};

static const auto _mtl_content_parser = [](const std::string &line, zap::abstract::MaterialInfo &current_material, const std::string &texture_directory) {
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == "map_Kd") {
        std::string texture_path;
        iss >> texture_path;
        current_material.diffuse_map = _find_texture_file(texture_path, texture_directory);

    } else if (command == "map_Bump") {
        std::string texture_path;
        std::string token;

        while (iss >> token) {
            if (token[0] != '-') {
                texture_path = token;
                break;
            }
            iss >> token;
        }

        if (!texture_path.empty()) {
            current_material.normal_map = _find_texture_file(texture_path, texture_directory);
        }

    } else if (command == "map_d") {
        std::string texture_path;
        iss >> texture_path;
        current_material.alpha_map = _find_texture_file(texture_path, texture_directory);

    } else if (command == "map_Ks") {
        std::string texture_path;
        iss >> texture_path;
        current_material.specular_map = _find_texture_file(texture_path, texture_directory);
    }
};

/**
* parsers
*/

static std::vector<zap::abstract::MaterialInfo> _parse_mtl_file(const std::string &mtl_path, const std::string &texture_directory)
{
    zap::abstract::MaterialInfo current_material;

    const auto parser = [&](const std::string &line, std::vector<zap::abstract::MaterialInfo> &materials) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "newmtl") {
            if (!current_material.name.empty()) {
                materials.push_back(current_material);
            }
            current_material = zap::abstract::MaterialInfo();
            iss >> current_material.name;
        } else {
            _mtl_content_parser(line, current_material, texture_directory);
        }
    };

    std::vector<zap::abstract::MaterialInfo> materials = zap::Filename::parseFile(mtl_path, parser, std::vector<zap::abstract::MaterialInfo>());

    if (!current_material.name.empty()) {
        materials.push_back(current_material);
    }

    return materials;
}

static std::string _get_mtl_file(const std::string &obj_file)
{
    const std::string mtl_filename = zap::Filename::parseFile(obj_file, _mtl_filename_worker, std::string());

    if (mtl_filename.empty()) {
        return "";
    }

    const std::filesystem::path obj_path(obj_file);
    const std::filesystem::path mtl_path = obj_path.parent_path() / mtl_filename;

    return mtl_path.string();
}

/**
 * protected
 */

void zap::abstract::ModelBase::_load_textures(const std::string &obj_file, const std::string &texture_directory)
{
    if (!Filename::exists(obj_file)) {
        throw exception::Error("ModelBase::_load_textures", "Object file does not exist: ", obj_file);
    }
    if (!texture_directory.empty() && !Filename::exists(texture_directory)) {
        throw exception::Error("ModelBase::_load_textures", "Texture directory does not exist: ", texture_directory);
    }

    _model = LoadModel(obj_file.c_str());
    if (_model.meshCount == 0) {
        throw exception::Error("ModelBase::_load_textures", "Failed to load model from ", obj_file);
    }

    /** @brief texture binded to 0 -> means no texture */
    _texture.id = 0;

    const std::string mtl_file = _get_mtl_file(obj_file);
    const std::vector<MaterialInfo> materials = _parse_mtl_file(mtl_file, texture_directory);

    if (materials.empty()) {
        return;
    }

    _bind_textures(materials);
}

/**
* private
*/

static std::unordered_map<std::string, Texture2D> _texture_cache;

void zap::abstract::ModelBase::_bind_textures(const std::vector<MaterialInfo> &materials)
{
    for (u64 i = 0; i < materials.size() && i < static_cast<u64>(_model.materialCount); ++i) {

        const MaterialInfo &material = materials[i];

        if (!material.diffuse_map.empty()) {

            if (_texture_cache.find(material.diffuse_map) != _texture_cache.end()) {
                /** @brief reuse cached texture */
                _model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = _texture_cache[material.diffuse_map];
                continue;
            }

            Texture2D diffuse_texture = LoadTexture(material.diffuse_map.c_str());

            if (diffuse_texture.id != 0) {

                /** @brief cache the texture for future use */
                _texture_cache[material.diffuse_map] = diffuse_texture;

                /** @brief apply the texture to the material */
                _model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = diffuse_texture;

                /** @brief save the first texture as the main texture */
                if (i == 0) {
                    _texture = diffuse_texture;
                }

            } else {
                throw exception::Error("ModelBase::_bind_textures", "Failed to load diffuse texture: ", material.diffuse_map);
            }
        }

        /** @brief load normal texture if normal map is present */
        if (!material.normal_map.empty()) {

            if (_texture_cache.find(material.normal_map) != _texture_cache.end()) {
                /** @brief reuse cached texture */
                _model.materials[i].maps[MATERIAL_MAP_NORMAL].texture = _texture_cache[material.normal_map];
                continue;
            }

            Texture2D normal_texture = LoadTexture(material.normal_map.c_str());

            if (normal_texture.id != 0) {

                /** @brief cache the texture for future use */
                _texture_cache[material.normal_map] = normal_texture;

                _model.materials[i].maps[MATERIAL_MAP_NORMAL].texture = normal_texture;
            } else {
                throw exception::Error("ModelBase::_bind_textures", "Failed to load normal texture: ", material.normal_map);
            }
        }

        /** @brief load alpha texture if alpha map is present */
        if (!material.alpha_map.empty()) {

            Texture2D alpha_texture = LoadTexture(material.alpha_map.c_str());

            if (alpha_texture.id != 0) {
                _model.materials[i].maps[MATERIAL_MAP_METALNESS].texture = alpha_texture;
            } else {
                throw exception::Error("ModelBase::_bind_textures", "Failed to load alpha texture: ", material.alpha_map);
            }
        }
    }
}
