/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Sun.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <App/Sun/Sun.hpp>

#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Logger.hpp>

/**
* public
*/

zappy::Sun::Sun(const std::shared_ptr<zap::ZapCamera> &camera) : zap::ShaderModel(camera)
{
    _init();
    _model->setPosition({10.0f, 10.0f, 10.0f});
}

void zappy::Sun::draw() const
{
    const f32 time = static_cast<f32>(GetTime());

    _model->draw();

    for (u8 i = 0; i < 50; ++i) {
        const f32 x = static_cast<f32>(i * 137 % 100 - 50);
        const f32 y = static_cast<f32>(i * 97 % 100 - 50);
        const f32 z = static_cast<f32>(i * 73 % 100 - 50);

        if (Vector3Length({x, y, z}) > 15.0f) {
            const f32 twinkle = 0.5f + 0.5f * sinf(time * 3.0f + i);

            DrawSphere({x, y, z}, 0.05f, ColorAlpha(WHITE, twinkle));
        }
    }
}

void zappy::Sun::update()
{
    const f32 time = static_cast<f32>(GetTime());

    _rotation += 0.5f;
    SetShaderValue(_shader, _timeLoc, &time, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_shader, _viewPosLoc, &_camera->get().position, SHADER_UNIFORM_VEC3);

    zap::ShaderModel::update();
}

/**
* protected
*/

void zappy::Sun::_init()
{
    Mesh sun_mesh = GenMeshSphere(2.0f, 32, 32);
    Model sun_model = LoadModelFromMesh(sun_mesh);

    _model = std::make_shared<zap::ZapModel>(sun_model);

    _shader = LoadShader(zap::Filename::getPath(ZAP_SHADER_SUN_VERT).c_str(), zap::Filename::getPath(ZAP_SHADER_SUN_FRAG).c_str());

    _timeLoc = GetShaderLocation(_shader, "time");
    _viewPosLoc = GetShaderLocation(_shader, "viewPos");

    _model->setShader(_shader);
    zap::logger::debug("Sun shader loaded with ID: ", _shader.id);
}
