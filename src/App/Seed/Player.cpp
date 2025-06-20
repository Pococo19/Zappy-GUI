/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Player.cpp
*/

#include "App/Maths/Maths.hpp"
#include "App/Seed/Create.hpp"
#include "Create.hpp"

#define MIN_DISTANCE 2.0f
#define MAX_ATTEMPTS 100
#define COUNT_RANDOM_RANGE (2.5f, 3.0f)

static const std::vector<std::string> _player_models = {
    zap::Filename::getPath("assets/models/Player2.obj"),
};

static void _seed(std::shared_ptr<zap::render::Scene> &scene, const std::vector<std::string> &obj_paths, const f32 radius, const u32 count, const Vector3 &scale)
{
    constexpr Vector3 center = {0, 0, 0};

    for (u32 i = 0; i < count; ++i) {
        Vector3 pos;

        for (u32 attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
            const f32 theta = static_cast<f32>(M_PI * (std::rand() / static_cast<f64>(RAND_MAX)));    //<< 0 to π
            const f32 phi = static_cast<f32>(2.0 * M_PI * (std::rand() / static_cast<f64>(RAND_MAX)));//<< 0 to 2π

            pos = {radius * sinf(theta) * cosf(phi), radius * cosf(theta), radius * sinf(theta) * sinf(phi)};
            pos = Vector3Add(center, pos);

            if (!zappy::create::is_too_close(pos, MIN_DISTANCE)) {
                break;
            }
        }

        zappy::create::__positions.push_back(pos);

        const auto obj = zappy::create::model(obj_paths[(zappy::maths::random<u32>(0, static_cast<u32>(obj_paths.size() - 1)))], pos);

        f32 angle;
        const Vector3 rotation = zappy::maths::rotation(pos, &angle);

        obj->setRotationAxis(rotation, angle);
        obj->setScale(scale);

        scene->add(std::move(obj));
    }
}

[[nodiscard]] static u32 _get_count(const f32 radius)
{
    const f32 spacing_offset = zappy::maths::random<f32> COUNT_RANDOM_RANGE;

    /** @brief A = 4πr² */
    const f32 surface = 4.f * PI * radius * radius;
    const f32 count = spacing_offset * spacing_offset;

    return static_cast<u32>(surface / count);
}

[[nodiscard]] static constexpr Vector3 _get_scale(const f32 radius, const u32 width, const u32 height)
{
    const f32 scale_factor = std::max(static_cast<f32>(width), static_cast<f32>(height)) / (2.0f * radius) / 10;

    return {scale_factor, scale_factor, scale_factor};
}

void zappy::create::player(std::shared_ptr<zap::render::Scene> &scene, const f32 radius, const u32 width, const u32 height)
{
    const u32 count = _get_count(radius);
    const Vector3 scale = _get_scale(radius, width, height);

    _seed(scene, _player_models, radius, count, scale);
}
