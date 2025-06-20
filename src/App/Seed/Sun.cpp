/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Sun.cpp
*/

#include <App/Seed/Create.hpp>
#include <App/Sun/Sun.hpp>

void zappy::create::sun(std::shared_ptr<zap::render::Scene> &scene, std::shared_ptr<zap::ZapCamera> &camera, const f32 radius)
{
    auto sun = std::make_shared<zappy::Sun>(camera, radius);

    scene->add(sun);
}
