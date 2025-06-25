/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Player.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include "App/Protocol/Callback.hpp"
#include "ZapGUI/Error.hpp"
#include <App/AI/Player.hpp>
#include <App/Maths/Maths.hpp>
#include <App/Seed/Create.hpp>

#include <iostream>

void zappy::create::player(std::shared_ptr<zap::render::Scene> &scene, const f32 radius, const Vector2u &size)
{
    protocol::Callback::getInstance().add("pnw", [&](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 6);

        if (params.size() < 6) {
            throw zap::exception::Error("PNW", "Invalid parameters count: ", params.size());
        }

        const std::string &id = params[0];
        const Vector2f base = {std::stof(params[1]), std::stof(params[2])};
        const Vector2f uv = {base._x / static_cast<f32>(size._x), base._y / static_cast<f32>(size._y)};
        const Vector3 pos = maths::to_sphere(uv, radius);
        std::cout << "Player " << id << " spawned at position: " << pos << std::endl;
    });
    (void) scene;
}
