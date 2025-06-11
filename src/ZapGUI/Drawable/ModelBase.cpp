/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ModelBase.cpp
*/

#include <ZapGUI/Drawable/ModelBase.hpp>
#include <ZapGUI/Error.hpp>
#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Logger.hpp>

#include <filesystem>
#include <iostream>

/**
* public setters and getters
*/

void zap::abstract::ModelBase::setPosition(const Vector3 &position)
{
    _position = position;
}

Vector3 zap::abstract::ModelBase::getPosition() const
{
    return _position;
}

void zap::abstract::ModelBase::setScale(f32 scale)
{
    _scale = scale;
}

f32 zap::abstract::ModelBase::getScale() const
{
    return _scale;
}

void zap::abstract::ModelBase::setTint(const Color &tint)
{
    _tint = tint;
}

Color zap::abstract::ModelBase::getTint() const
{
    return _tint;
}

/**
* protected
*/

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

    const std::string mtl_file = Filename::getPath(_get_mtl_file(obj_file));
    const std::vector<MaterialInfo> materials = _parse_mtl_file(mtl_file, texture_directory);

    if (materials.empty()) {
        logger::debug("ModelBase::_load_textures", "No materials found in MTL file: ", mtl_file);
        return;
    }

    _bind_textures(materials);

    logger::debug("ModelBase::_load_textures", "Texture loading completed for ", obj_file);
}

/**
* private
*/

void zap::abstract::ModelBase::_bind_textures(const std::vector<MaterialInfo> &materials)
{
    for (size_t i = 0; i < materials.size() && i < (size_t) _model.materialCount; ++i) {

        const MaterialInfo &material = materials[i];

        logger::task_start("processing material: ", material.name);

        if (!material.diffuse_map.empty()) {
            logger::task_start("loading diffuse texture: ", material.diffuse_map);

            Texture2D diffuse_texture = LoadTexture(material.diffuse_map.c_str());

            if (diffuse_texture.id != 0) {
                /** @brief apply the texture to the material */
                _model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = diffuse_texture;

                /** @brief save the first texture as the main texture */
                if (i == 0) {
                    _texture = diffuse_texture;
                }

                logger::task_done("successfully loaded diffuse texture for material ", material.name);
            } else {
                throw exception::Error("ModelBase::_bind_textures", "Failed to load diffuse texture: ", material.diffuse_map);
            }
        }

        /** @brief load normal texture if normal map is present */
        if (!material.normal_map.empty()) {
            logger::task_start("loading normal texture: ", material.normal_map);

            Texture2D normal_texture = LoadTexture(material.normal_map.c_str());

            if (normal_texture.id != 0) {
                _model.materials[i].maps[MATERIAL_MAP_NORMAL].texture = normal_texture;
                logger::task_done("successfully loaded normal texture for material ", material.name);
            } else {
                throw exception::Error("ModelBase::_bind_textures", "Failed to load normal texture: ", material.normal_map);
            }
        }

        /** @brief load alpha texture if alpha map is present */
        if (!material.alpha_map.empty()) {
            logger::task_start("loading alpha texture: ", material.alpha_map);

            Texture2D alpha_texture = LoadTexture(material.alpha_map.c_str());

            if (alpha_texture.id != 0) {
                _model.materials[i].maps[MATERIAL_MAP_METALNESS].texture = alpha_texture;
                logger::task_done("successfully loaded alpha texture for material ", material.name);
            } else {
                throw exception::Error("ModelBase::_bind_textures", "Failed to load alpha texture: ", material.alpha_map);
            }
        }

        logger::task_done("processing material: ", material.name);
    }
}
