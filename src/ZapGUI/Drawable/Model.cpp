/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ZapModel.cpp
*/

#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Error.hpp>
#include <ZapGUI/Filename.hpp>

/**
* public
*/

zap::ZapModel::ZapModel(const std::string &obj_path, const std::string &texture_directory)
{
    _load_textures(obj_path, texture_directory);
}

zap::ZapModel::ZapModel(const Model &model, const Texture &texture)
{
    _model = model;
    if (_model.meshCount == 0) {
        throw exception::Error("ZapModel::ZapModel", "Failed to load model from provided Model object");
    }
    _texture.id = 0;
    _texture = texture;
}

zap::ZapModel::~ZapModel()
{
    UnloadModel(_model);
    if (_texture.id != 0) {
        UnloadTexture(_texture);
    }
}

void zap::ZapModel::draw() const
{
    DrawModel(_model, _position, _scale, _tint);
}

/**
* static
*/

std::unique_ptr<zap::ZapModel> zap::ZapModel::from_heightmap(const std::string &heightmap_path, const std::string &texture_path)
{
    if (!Filename::exists(heightmap_path)) {
        throw exception::Error("zap::ZapModel::from_heightmap", "File not found: ", heightmap_path);
    }
    if (!texture_path.empty() && !Filename::exists(texture_path)) {
        throw exception::Error("zap::ZapModel::from_heightmap", "Texture file not found: ", texture_path);
    }

    Image heightmap = LoadImage(heightmap_path.c_str());
    const Vector3 size = {
        static_cast<f32>(heightmap.width),//<< X = width of image
        30.0f,                            //<< Y = max height (e.g. 30.0f)
        static_cast<f32>(heightmap.height)//<< Z = depth of image
    };
    Mesh mesh = GenMeshHeightmap(heightmap, size);

    UnloadImage(heightmap);

    Model model = LoadModelFromMesh(mesh);

    if (!texture_path.empty()) {
        Texture2D texture = LoadTexture(texture_path.c_str());

        SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);
        SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);
    }

    return std::make_unique<zap::ZapModel>(model);
}
