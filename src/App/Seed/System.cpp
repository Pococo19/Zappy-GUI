/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** System.cpp
*/

#include <App/Seed/Create.hpp>
#include <App/Stars/Slavia.hpp>
#include <App/Stars/Sun.hpp>

void zappy::create::system(std::shared_ptr<zap::render::Scene> &scene, std::shared_ptr<zap::ZapCamera> &camera, std::shared_ptr<BasePlanet> zappy)
{
    const f32 zappy_radius = zappy->getRadius();

    auto sun = std::make_shared<zappy::Sun>(camera, zappy_radius);
    sun->addPlanet(zappy);

    auto slavia = std::make_shared<zappy::Slavia>(camera, zappy_radius);
    sun->addPlanet(slavia);

    scene->add(slavia);
    scene->add(sun);
}
