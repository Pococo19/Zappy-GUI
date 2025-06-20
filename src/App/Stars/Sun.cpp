/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Sun.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <App/Maths/Maths.hpp>
#include <App/Stars/Sun.hpp>

#include <ZapGUI/Filename.hpp>

/**
* public
*/

zappy::Sun::Sun(const std::shared_ptr<zap::ZapCamera> &camera, const f32 zappy_radius) : zap::ShaderModel(camera)
{
    _init();
    _model->setPosition({zappy_radius * 4.5f + zappy_radius, 0.0f, 0.0f});
    _zappy_radius = zappy_radius + 0.5f;
    _stars = LoadModelFromMesh(GenMeshSphere(0.05f, 4, 4));
}

void zappy::Sun::addPlanet(const std::shared_ptr<zappy::BasePlanet> &planet)
{
    _planets.push_back(planet);
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

void zappy::Sun::update(const f32 dt)
{
    constexpr Vector3 light_color = {1.0f, 0.95f, 0.8f};
    constexpr f32 light_intensity = 1.0f;

    /** @brief orbit the sun around the center of the zappy planet lol */
    const Vector3 orbit_position = maths::orbit_position(0.2f, _zappy_radius, dt, 5.5f);

    _model->setPosition(orbit_position);

    /** @brief rotate the sun around its own axis */
    _rotation += 0.5f;
    _model->setRotation({0.0f, _rotation, 0.0f});

    SetShaderValue(_shader, _timeLoc, &dt, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_shader, _viewPosLoc, &_camera->get().position, SHADER_UNIFORM_VEC3);

    for (const auto &planet : _planets) {
        planet->applyLighting(orbit_position, light_color, light_intensity);
    }
}

/**
* protected
*/

void zappy::Sun::_init()
{
    const Mesh sun_mesh = GenMeshSphere(2.0f, 64, 64);
    const Model sun_model = LoadModelFromMesh(sun_mesh);

    _model = std::make_shared<zap::ZapModel>(sun_model);
    _shader = LoadShader(zap::Filename::getPath(ZAP_SHADER_SUN_VERT).c_str(), zap::Filename::getPath(ZAP_SHADER_SUN_FRAG).c_str());

    _timeLoc = GetShaderLocation(_shader, "time");
    _viewPosLoc = GetShaderLocation(_shader, "viewPos");

    _model->setShader(_shader);

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
