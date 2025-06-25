/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Rocks.cpp
*/

#include <App/Maths/Maths.hpp>
#include <App/Seed/Create.hpp>

static const std::vector<std::string> _rocks_models = {
    zap::Filename::getPath("assets/models/Pebble_Round_1.obj"),
    zap::Filename::getPath("assets/models/Pebble_Round_2.obj"),
    zap::Filename::getPath("assets/models/Pebble_Round_3.obj"),
    zap::Filename::getPath("assets/models/Pebble_Round_4.obj"),
    zap::Filename::getPath("assets/models/Pebble_Round_5.obj"),
    zap::Filename::getPath("assets/models/Pebble_Square_1.obj"),
    zap::Filename::getPath("assets/models/Pebble_Square_2.obj"),
    zap::Filename::getPath("assets/models/Pebble_Square_3.obj"),
    zap::Filename::getPath("assets/models/Pebble_Square_4.obj"),
    zap::Filename::getPath("assets/models/Pebble_Square_5.obj"),
    zap::Filename::getPath("assets/models/Pebble_Square_6.obj"),
};

static void _push_resource(const zappy::protocol::Resource &resource, std::shared_ptr<zap::render::Scene> &out_scene, const Vector3 &position, const Vector3 &scale)
{
    constexpr u64 size = sizeof(_rocks_models) / sizeof(_rocks_models[0]);
    constexpr f32 offset_range = 0.02f;// << small offset to keep resources within tile bounds
    constexpr Vector3 center = {0.0f, 0.0f, 0.0f};
    constexpr Vector3 up = {0.0f, 1.0f, 0.0f};

    for (u32 instance = 0; instance < resource.quantity; ++instance) {
        const f32 random_x = zappy::maths::random<f32>(-offset_range, offset_range);
        const f32 random_y = zappy::maths::random<f32>(-offset_range, offset_range);
        const f32 random_z = zappy::maths::random<f32>(-offset_range, offset_range);
        const Vector3 offset = {random_x, random_y, random_z};
        const Vector3 final_position = Vector3Add(position, offset);

        const auto model = zappy::create::model(_rocks_models[static_cast<u32>(zappy::maths::random(0, static_cast<i32>(size)))], final_position);

        const Vector3 normal = Vector3Normalize(Vector3Subtract(position, center));
        const Vector3 axis = Vector3CrossProduct(up, normal);
        const f32 angle = acosf(Vector3DotProduct(up, normal));

        if (Vector3Length(axis) > EPSILON) {
            model->setRotationAxis(axis, angle * RAD2DEG);
        }

        model->setScale(scale);
        out_scene->add(model);
    }
}

void zappy::create::rocks(const protocol::GUI_Map &map, std::shared_ptr<zap::render::Scene> &out_scene, const f32 radius)
{
    const u32 width = static_cast<u32>(map.front().size());
    const u32 height = static_cast<u32>(map.size());
    const Vector3 scale = get_scale(radius, width, height, 15);

    for (u32 y = 0; y < height; ++y) {
        for (u32 x = 0; x < width; ++x) {

            const auto &tile = map[y][x];
            const Vector2f base_uv = {static_cast<f32>(x) / static_cast<f32>(width), static_cast<f32>(y) / static_cast<f32>(height)};
            const Vector3 base_position = maths::to_sphere(base_uv, radius);

            for (u32 res_idx = 0; res_idx < ZAP_MAX_RESOURCES; ++res_idx) {
                const auto &resource = tile[res_idx];

                if (resource.quantity <= 0 || resource.type == zappy::protocol::ResourceType::UNKNOWN) {
                    continue;
                }

                _push_resource(resource, out_scene, base_position, scale);
            }
        }
    }
}
