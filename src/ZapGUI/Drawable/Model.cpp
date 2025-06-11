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

zap::ZapModel::ZapModel(const Model &model)
{
    _model = model;
    if (_model.meshCount == 0) {
        throw exception::Error("ZapModel::ZapModel", "Failed to load model from provided Model object");
    }
    _texture.id = 0;
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

std::unique_ptr<zap::ZapModel> zap::ZapModel::from_heightmap(const std::string &obj_path)
{
    if (!Filename::exists(obj_path)) {
        throw exception::Error("zap::ZapModel::from_heightmap", "File not found: ", obj_path);
    }

    Image heightmap = LoadImage(obj_path.c_str());
    Texture2D texture = LoadTextureFromImage(heightmap);
    Mesh mesh = GenMeshHeightmap(heightmap, Vector3(16, 8, 16));

    UnloadImage(heightmap);

    Model model = LoadModelFromMesh(mesh);

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    return std::make_unique<zap::ZapModel>(model);
}
