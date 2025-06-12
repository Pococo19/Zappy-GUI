/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ShaderModel.cpp
*/

#include "ZapGUI/Error.hpp"
#include <ZapGUI/Drawable/ShaderModel.hpp>
#include <ZapGUI/Filename.hpp>

/**
* public
*/

zap::ShaderModel::ShaderModel(Shader &shader, std::shared_ptr<ZapModel> model, std::shared_ptr<ZapCamera> camera) : _model(model), _camera(camera), _shader(shader)
{
    if (_shader.id == 0) {
        throw exception::Error("ShaderModel::ShaderModel", "Failed to load shader: ", shader.id);
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
