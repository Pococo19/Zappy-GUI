/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ShaderModel.cpp
*/

#include "ZapGUI/Error.hpp"
#include "ZapGUI/Logger.hpp"
#include <ZapGUI/Drawable/ShaderModel.hpp>
#include <ZapGUI/Filename.hpp>

/**
* public
*/

zap::ShaderModel::ShaderModel(std::shared_ptr<ZapCamera> camera) : _camera(camera)
{
    _init();
    if (_shader.id == 0) {
        throw exception::Error("ShaderModel::ShaderModel", "Failed to load shader: ", _shader.id);
    }
}

zap::ShaderModel::~ShaderModel()
{
    if (_shader.id != 0) {
        UnloadShader(_shader);
    }
}

void zap::ShaderModel::update()
{
    /* __update__ */
}

void zap::ShaderModel::draw() const
{
    BeginShaderMode(_shader);
    _model->draw();
    EndShaderMode();
}

/**
* protected
*/

void zap::ShaderModel::_init()
{
    zap::logger::debug("MARCHE PAS");
}
