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

static constexpr Color _get_tint(const zappy::protocol::ResourceType type)
{
    switch (type) {
        case zappy::protocol::ResourceType::FOOD:
            return BROWN;
        case zappy::protocol::ResourceType::LINEMATE:
            return BLUE;
        case zappy::protocol::ResourceType::DERAUMERE:
            return RED;
        case zappy::protocol::ResourceType::SIBUR:
            return GREEN;
        case zappy::protocol::ResourceType::MENDIANE:
            return PURPLE;
        case zappy::protocol::ResourceType::PHIRAS:
            return ORANGE;
        case zappy::protocol::ResourceType::THYSTAME:
            return YELLOW;
        default:
            return WHITE;
    }
}

static void _push_resource(const zappy::protocol::Resource &resource, std::shared_ptr<zap::render::Scene> &out_scene, const Vector3 &position)
{
    constexpr u64 size = sizeof(_rocks_models) / sizeof(_rocks_models[0]);
    constexpr f32 offset_range = 0.02f;// << small offset to keep resources within tile bounds

    for (u32 instance = 0; instance < resource.quantity; ++instance) {
        const f32 random_x = zappy::maths::random<f32>(-offset_range, offset_range);
        const f32 random_y = zappy::maths::random<f32>(-offset_range, offset_range);
        const f32 random_z = zappy::maths::random<f32>(-offset_range, offset_range);
        const Vector3 offset = {random_x, random_y, random_z};
        const Vector3 final_position = Vector3Add(position, offset);

        const auto model = zappy::create::model(_rocks_models[static_cast<u32>(zappy::maths::random(0, static_cast<i32>(size)))], final_position);

        model->setTint(_get_tint(resource.type));

        out_scene->add(model);
    }
}

void zappy::create::rocks(const protocol::GUI_Map &map, std::shared_ptr<zap::render::Scene> &out_scene, const f32 radius)
{
    const u32 width = static_cast<u32>(map.front().size());
    const u32 height = static_cast<u32>(map.size());

    for (u32 y = 0; y < height; ++y) {
        for (u32 x = 0; x < width; ++x) {

            const auto &tile = map[y][x];
            const Vector2f base_uv = {static_cast<f32>(x) / static_cast<f32>(width), static_cast<f32>(y) / static_cast<f32>(height)};
            const Vector3 base_position = maths::to_sphere(base_uv, radius);

            for (u32 res_idx = 0; res_idx < 7; ++res_idx) {
                const auto &resource = tile[res_idx];

                if (resource.quantity <= 0 || resource.type == zappy::protocol::ResourceType::UNKNOWN) {
                    continue;
                }

                _push_resource(resource, out_scene, base_position);
            }
        }
    }
}
