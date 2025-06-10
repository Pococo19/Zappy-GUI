/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ZapModel.cpp
*/

#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Error.hpp>

/**
* public
*/

zap::ZapModel::ZapModel(const std::string &obj_path, const std::string &texture_directory)
{
    _load_textures(obj_path, texture_directory);
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
