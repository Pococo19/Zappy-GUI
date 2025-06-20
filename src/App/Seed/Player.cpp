/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Player.cpp
*/

#include <App/Seed/Create.hpp>

static const std::vector<std::string> _player_models = {
    zap::Filename::getPath("assets/models/Player2.obj"),
};

void zappy::create::player(std::shared_ptr<zap::render::Scene> &scene, const f32 radius, const u32 width, const u32 height)
{
    const u32 count = get_count(radius);
    const Vector3 scale = get_scale(radius, width, height);

    seed(scene, _player_models, radius, count, scale);
}
