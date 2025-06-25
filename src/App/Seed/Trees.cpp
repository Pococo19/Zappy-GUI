/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Trees.cpp
*/

#include <App/Seed/Create.hpp>

// clang-format off
static const std::vector<std::string> _tree_models = {
    zap::Filename::getPath("assets/models/CommonTree_1.obj"),
    zap::Filename::getPath("assets/models/CommonTree_2.obj"),
    zap::Filename::getPath("assets/models/CommonTree_3.obj"),
    zap::Filename::getPath("assets/models/CommonTree_4.obj"),
};

static const std::vector<std::string> _flower_models = {
    zap::Filename::getPath("assets/models/Flower_3_Group.obj"),
    zap::Filename::getPath("assets/models/Flower_4_Group.obj"),
    zap::Filename::getPath("assets/models/Mushroom_Common.obj"),
    zap::Filename::getPath("assets/models/Mushroom_Laetiporus.obj"),
    zap::Filename::getPath("assets/models/Grass_Common_Tall.obj"),
    zap::Filename::getPath("assets/models/Grass_Common_Short.obj"),
    zap::Filename::getPath("assets/models/Grass_Wispy_Tall.obj"),
    zap::Filename::getPath("assets/models/Grass_Wispy_Short.obj")
};
// clang-format on

void zappy::create::trees(std::shared_ptr<zap::render::Scene> &out_scene, const f32 radius, const Vector2u &map_size)
{
    const u32 count = get_count(radius);
    const Vector3 scale = get_scale(radius, map_size._x, map_size._y, 15);

    seed(out_scene, _tree_models, radius, count, scale);
    seed(out_scene, _flower_models, radius, count * 4, scale);
}
