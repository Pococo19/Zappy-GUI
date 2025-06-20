/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ShaderModel.cpp
*/

#include <ZapGUI/Drawable/ShaderModel.hpp>
#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Macro.hpp>

/**
* public
*/

zap::ShaderModel::ShaderModel(std::shared_ptr<ZapCamera> camera)
{
    if (camera == nullptr) {
        return;
    }
    _camera = camera;
}

zap::ShaderModel::~ShaderModel()
{
    if (_shader.id != 0) {
        UnloadShader(_shader);
    }
}

void zap::ShaderModel::update(const f32 UNUSED dt)
{
    /* __update__ */
}

void zap::ShaderModel::draw() const
{
    BeginShaderMode(_shader);
    _model->draw();
    EndShaderMode();
}
