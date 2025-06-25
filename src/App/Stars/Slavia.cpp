/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Slavia.cpp
*/

#include <App/Maths/Maths.hpp>
#include <App/Stars/Slavia.hpp>

#define SLAVIA_COLOR {0.8f, 0.3f, 0.1f}
#define SLAVIA_RADIUS_MULTIPLIER 0.75f
#define SLAVIA_INCLINATION_DEG 23.5f

#define SLAVIA_SPEED 0.5f
#define SLAVIA_OFFSET 4.5f
#define SLAVIA_ROTATION_SPEED 0.6f

/**
* public
*/

zappy::Slavia::Slavia(std::shared_ptr<zap::ZapCamera> camera, const f32 zappy_radius) : BasePlanet(camera)
{
    _zappy_radius = zappy_radius;
    _radius = zappy_radius * SLAVIA_RADIUS_MULTIPLIER;
    _init(zappy_radius);
    _model->setShader(_shader);
    setColor(SLAVIA_COLOR);
}

void zappy::Slavia::update(const f32 dt)
{
    constexpr f32 inclination_deg = SLAVIA_INCLINATION_DEG;
    constexpr f32 inclination_rad = inclination_deg * DEG2RAD;

    Vector3 pos = maths::orbit_position(SLAVIA_SPEED, _zappy_radius, dt, SLAVIA_OFFSET);

    const f32 y = pos.y * cosf(inclination_rad) - pos.z * sinf(inclination_rad);
    const f32 z = pos.y * sinf(inclination_rad) + pos.z * cosf(inclination_rad);

    pos.y = y;
    pos.z = z;

    _model->setPosition(pos);
    _rotation += SLAVIA_ROTATION_SPEED;
    zappy::BasePlanet::update(dt);
}

/**
 * private
 */

void zappy::Slavia::_init(const f32 zappy_radius)
{
    const Vector3 position = {zappy_radius * 2.0f, 0.0f, 0.0f};
    Mesh deformed_mesh = GenMeshSphere(_radius, 64, 64);

    UploadMesh(&deformed_mesh, false);

    const Model model = LoadModelFromMesh(deformed_mesh);

    _model = std::make_shared<zap::ZapModel>(model);
    _model->setPosition(position);
    _rotation = 0.0f;
}
