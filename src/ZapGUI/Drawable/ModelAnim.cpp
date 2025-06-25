/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** ModelAnim.cpp
*/

#include <ZapGUI/Drawable/ModelAnim.hpp>
#include <ZapGUI/Error.hpp>
#include <ZapGUI/Event/EventCallback.hpp>
#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Macro.hpp>

/*
* public
*/

zap::ZapModelAnim::ZapModelAnim(const std::string &glb_path)
{
    _load_glb_animated(glb_path);
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
    const auto &anim = _animations[_anim_index];

    _frame = (_frame + 1) % anim.frameCount;
    UpdateModelAnimation(_model, anim, _frame);
}

/*
* private
*/

void zap::ZapModelAnim::_load_glb_animated(const std::string &glb_path)
{
    if (!Filename::exists(glb_path)) {
        throw exception::Error("zap::ZapModelAnim::_load_glb_animated", "File not found: ", glb_path);
    }

    const char *path = glb_path.c_str();

    _model = LoadModel(path);
    _animations = LoadModelAnimations(path, &_anim_count);

    if (_model.meshCount == 0 || !_animations || _anim_count == 0) {
        throw exception::Error("zap::ZapModelAnim::_load_glb_animated", "Failed to load model or animations: ", glb_path);
    }

    event::EventCallback::getInstance().add(KEY_RIGHT, [&]() { _anim_index = (_anim_index + 1) % _anim_count; });
}
