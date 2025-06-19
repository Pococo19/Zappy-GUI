/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Sun.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <App/Maths/Maths.hpp>
#include <App/Sun/Sun.hpp>

#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Logger.hpp>

/**
* public
*/

zappy::Sun::Sun(const std::shared_ptr<zap::ZapCamera> &camera, const f32 planet_radius) : zap::ShaderModel(camera)
{
    _init();
    _model->setPosition({planet_radius * 4.5f + planet_radius, 0.0f, 0.0f});
    _planet_radius = planet_radius;
    _stars = LoadModelFromMesh(GenMeshSphere(0.05f, 4, 4));
}

void zappy::Sun::draw() const
{
    const f32 time = static_cast<f32>(GetTime());

    _model->draw();

    for (u32 i = 0; i < _stars_positions.size(); ++i) {
        const Vector3 &pos = _stars_positions[i];
        const f32 twinkle = 0.5f + 0.5f * sinf(time * 3.0f + static_cast<f32>(i));

        DrawModelEx(_stars, pos, {0, 1, 0}, 0.0f, {1, 1, 1}, ColorAlpha(WHITE, twinkle));
    }
}

void zappy::Sun::update()
{
    const f32 time = static_cast<f32>(GetTime());

    /** @brief orbit the sun around the center of the planet lol */
    const float orbit_radius = _planet_radius * 4.5f + _planet_radius;
    const float orbit_speed = 0.2f;

    Vector3 orbit_position = {orbit_radius * cosf(time * orbit_speed), 0.0f, orbit_radius * sinf(time * orbit_speed)};
    _model->setPosition(orbit_position);

    /** @brief rotate the sun around its own axis */
    _rotation += 0.5f;
    _model->setRotation({0.0f, _rotation, 0.0f});

    SetShaderValue(_shader, _timeLoc, &time, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_shader, _viewPosLoc, &_camera->get().position, SHADER_UNIFORM_VEC3);
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

    for (u32 i = 0; i < 500; ++i) {
        const f32 theta = maths::random<f32>(0.0f, 2.0f * PI);
        const f32 phi = acosf(maths::random<f32>(-1.0f, 1.0f));

        const f32 x = sinf(phi) * cosf(theta);
        const f32 y = sinf(phi) * sinf(theta);
        const f32 z = cosf(phi);

        const f32 radius = maths::random<f32>(15.0f, 50.0f);

        _stars_positions.push_back({x * radius, y * radius, z * radius});
    }
}
