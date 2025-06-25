/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Player.cpp
*/

#include <App/Maths/Maths.hpp>
#include <App/Seed/Create.hpp>

static const std::string _player_models = {
    zap::Filename::getPath("assets/models/Bot.glb"),
};

void zappy::create::player(std::shared_ptr<zap::render::Scene> &scene, const f32 radius, const Vector2u &size)
{
    constexpr Vector2f vec2_pos = {7, 2};
    const Vector2f uv = {vec2_pos._x / static_cast<f32>(size._x), vec2_pos._y / static_cast<f32>(size._y)};
    const Vector3 scale = get_scale(radius, size._x, size._y, 500.f);
    const Vector3 position = maths::to_sphere(uv, radius);
    const auto mandela = model_anim(_player_models, position);

    mandela->setScale(scale);
    constexpr f32 angle = 90;
    constexpr Vector3 rotation = {1.f, 0.f, 0.f};
    mandela->setRotationAxis(rotation, angle);
    scene->add(mandela);
}
