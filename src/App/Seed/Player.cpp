/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Player.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Threads.hpp>

#include <App/AI/Player.hpp>
#include <App/Maths/Maths.hpp>
#include <App/Protocol/Callback.hpp>
#include <App/Seed/Create.hpp>

#include <iostream>

void zappy::create::player(std::shared_ptr<zap::render::Scene> &out_scene, const f32 radius, const Vector2u &size)
{
    std::weak_ptr<zap::render::Scene> weak_scene = out_scene;

    protocol::Callback::getInstance().add("pnw", [weak_scene, radius, size](const std::string &data) -> void {
        std::cout << "pnw: " << data << std::endl;
        if (!protocol::_ready) {
            std::cout << "pnw: not ready, waiting for protocol to be ready" << std::endl;
            await
        }
        std::cout << "pnw: protocol ready, parsing data" << std::endl;

        const auto params = protocol::parse<std::string>(data, 6);
        if (params.size() < 6) {
            return;
        }

        f32 out_angle;

        const std::string id = params[0];
        const Vector2f base = {std::stof(params[1]), std::stof(params[2])};
        const Vector3 scale = get_scale(radius, size._x, size._y, 500.f);
        constexpr Vector3 orientation = {1.f, 0.f, 0.f};
        const Vector3 pos = maths::to_3D(base, size, radius);
        const Vector3 r = maths::rotation(pos, orientation, &out_angle);

        zap::thread::Queue::getInstance().push([weak_scene, id, pos, scale, r]() {
            const auto scene = weak_scene.lock();
            if (!scene) {
                return;
            }
            const auto player = std::make_shared<zappy::ai::Player>(id);
            player->setPosition(pos);
            player->setScale(scale);
            scene->add(player);
            std::cout << "added player " << id << " at position " << pos << std::endl;
        });
    });
}
