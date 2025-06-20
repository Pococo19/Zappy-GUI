/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Sun.cpp
*/

#include <App/Seed/Create.hpp>
#include <App/Stars/Sun.hpp>

void zappy::create::sun(std::shared_ptr<zap::render::Scene> &scene, std::shared_ptr<zap::ZapCamera> &camera, std::shared_ptr<BasePlanet> planet)
{
    auto sun = std::make_shared<zappy::Sun>(camera, planet->getRadius());

    sun->addPlanet(planet);
    scene->add(sun);
}
