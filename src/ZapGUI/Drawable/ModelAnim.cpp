/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** ModelAnim.cpp
*/

#include <ZapGUI/Drawable/ModelAnim.hpp>
#include <ZapGUI/Error.hpp>
#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Macro.hpp>
#include "ModelAnim.hpp"

#define ZAP_USE_RAYLIB_MATH

/*
* public
*/

zap::ZapModelAnim::ZapModelAnim(const std::string &glb_path)
{
    _load_glb_animated(glb_path);
}

zap::ZapModelAnim::ZapModelAnim(const Model &model)
{
    _model = model;
    if (_model.meshCount == 0) {
        throw exception::Error("ZapModelAnim::ZapModelAnim", "Failed to load model from provided Model object");
    }
    _texture.id = 0;
}

zap::ZapModelAnim::~ZapModelAnim()
{
    UnloadModel(_model);
    if (_texture.id != 0) {
        UnloadTexture(_texture);
    }
}

void zap::ZapModelAnim::draw() const
{
    DrawModelEx(_model, _position, _rotationAxis, _rotationAngle, _scale, _tint);
}

void zap::ZapModelAnim::update(const f32 UNUSED dt)
{
    if (_animations && _animCount > 0) {
        _frame += dt * 24.0f;
        if (_frame >= static_cast<f32>(_animations[0].frameCount)) _frame = 0.0f;
        UpdateModelAnimation(_model, _animations[0], static_cast<int>(_frame));
    }
}

/*
* static
*/

void zap::ZapModelAnim::_load_glb_animated(const std::string &glb_path)
{
    if (!Filename::exists(glb_path)) {
        throw exception::Error("zap::ZapModelAnim::_load_glb_animated", "File not found: ", glb_path);
    }

    _model = LoadModel(glb_path.c_str());
    _animations = LoadModelAnimations(glb_path.c_str(), &_animCount);

    if (_model.meshCount == 0 || !_animations || _animCount == 0) {
        throw exception::Error("zap::ZapModelAnim::_load_glb_animated", "Failed to load model or animations: ", glb_path);
    }

    _frame = 0;
    _scale = Vector3{1.0f, 1.0f, 1.0f};
    _tint = WHITE;
    _rotationAxis = Vector3{0.0f, 1.0f, 0.0f};
    _rotationAngle = 0.0f;
}
