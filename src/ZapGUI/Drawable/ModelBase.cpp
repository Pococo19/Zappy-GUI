/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ModelBase.cpp
*/

#include <ZapGUI/Drawable/ModelBase.hpp>
#include <ZapGUI/Error.hpp>
#include <ZapGUI/Filename.hpp>

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

void zap::abstract::ModelBase::setScale(float scale)
{
    _scale = scale;
}

float zap::abstract::ModelBase::getScale() const
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

    _texture.id = 0;
}
