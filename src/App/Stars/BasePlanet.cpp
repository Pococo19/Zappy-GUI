/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** BasePlanet.cpp
*/

#include "ZapGUI/Error.hpp"
#include <App/Stars/BasePlanet.hpp>
#include <ZapGUI/Filename.hpp>

/**
* public
*/

zappy::BasePlanet::BasePlanet(std::shared_ptr<zap::ZapCamera> camera) : zap::ShaderModel(camera)
{
    _setup_shader();
}

void zappy::BasePlanet::applyLighting(const Vector3 &light_pos, const Vector3 &light_color, const f32 light_intensity)
{
    if (_shader.id <= 0) {
        return;
    }
    SetShaderValue(_shader, _lightPosLoc, &light_pos, SHADER_UNIFORM_VEC3);
    SetShaderValue(_shader, _lightColorLoc, &light_color, SHADER_UNIFORM_VEC3);
    SetShaderValue(_shader, _lightIntensityLoc, &light_intensity, SHADER_UNIFORM_FLOAT);
}

void zappy::BasePlanet::draw() const
{
    _model->draw();
}

void zappy::BasePlanet::update(const f32 dt)
{
    if (_shader.id <= 0) {
        return;
    }

    SetShaderValue(_shader, _timeLoc, &dt, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_shader, _viewPosLoc, &_camera->get().position, SHADER_UNIFORM_VEC3);

    _rotation += 0.1f;
    const Vector3 rotation = {0.0f, _rotation, 0.0f};
    _model->setRotation(rotation);

    _model->update(dt);
}

/**
 * setters
 */

void zappy::BasePlanet::setColor(const Vector3 &color)
{
    _color = color;

    if (_shader.id > 0) {
        SetShaderValue(_shader, _planetBaseColorLoc, &_color, SHADER_UNIFORM_VEC3);
    }
}

/**
 * getters
 */

f32 zappy::BasePlanet::getRadius() const
{
    return _radius;
}

Vector3 zappy::BasePlanet::getPosition() const
{
    return _model ? _model->getPosition() : Vector3{0.0f, 0.0f, 0.0f};
}

/**
* protected
*/

void zappy::BasePlanet::_setup_shader()
{
    _shader = LoadShader(zap::Filename::getPath(ZAP_SHADER_PLANET_VERT).c_str(), zap::Filename::getPath(ZAP_SHADER_PLANET_FRAG).c_str());

    if (_shader.id <= 0) {
        throw zap::exception::Error("BasePlanet::_setup_shader", "Failed to load shader from files: ", ZAP_SHADER_PLANET_VERT, " and ", ZAP_SHADER_PLANET_FRAG);
    }

    _timeLoc = GetShaderLocation(_shader, "time");
    _viewPosLoc = GetShaderLocation(_shader, "viewPos");
    _lightPosLoc = GetShaderLocation(_shader, "lightPos");
    _lightColorLoc = GetShaderLocation(_shader, "lightColor");
    _lightIntensityLoc = GetShaderLocation(_shader, "lightIntensity");
    _planetBaseColorLoc = GetShaderLocation(_shader, "planetBaseColor");
}
