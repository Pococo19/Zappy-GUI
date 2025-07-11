/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Create.cpp
*/

#include <App/Application.hpp>
#include <App/Seed/Create.hpp>

#include <App/Stars/Zappy.hpp>
#include <iostream>

/**
 * main entry point WARN: do not change the signature
 */
std::shared_ptr<zap::render::Scene> zappy::_create_main_scene(const protocol::Data &data)
{
    auto scene = std::make_shared<zap::render::Scene>();
    auto camera = std::make_shared<zap::ZapCamera>();
    const auto zappy = std::make_shared<zappy::Zappy>(data.map, camera);
    const f32 zappy_radius = zappy->getRadius();
    const Vector3 zappy_position = zappy->getPosition();
    const u32 width = static_cast<u32>(data.map.front().size());
    const u32 height = static_cast<u32>(data.map.size());
    const Vector2u size = {width, height};

    ///////////////////////////////////////////////////////////////////////////////////////////////

    camera->setPosition({0.0f, 0.0f, zappy_radius * 2.5f});
    camera->setTarget(zappy_position);

    scene->add(camera);
    zappy->setCamera(camera);
    scene->add(zappy);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    create::rocks(data.map, scene, zappy_radius + 0.05f);
    create::trees(scene, zappy_radius, size);
    create::system(scene, camera, zappy);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    return scene;
}
