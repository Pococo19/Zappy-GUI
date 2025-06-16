/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** CreateObjects.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>

#include <App/Application.hpp>
#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Logger.hpp>

#include <ZapGUI/Filename.hpp>

#include <cmath>
#include <random>

/**
 * private struct, attributes and constants
 */
// clang-format off

struct Planet {
        f32 radius;
        Vector3 position;
        std::shared_ptr<zap::abstract::Drawable> model;
};

// clang-format on
/**
 * private functions
 */

static Planet _create_planet(const zappy::protocol::GUI_Map &map)
{
    if (map.empty() || map.front().empty()) {
        throw zap::exception::Error("CreatePlanet", "Map is empty or malformed (rows or columns are 0)");
    }

    constexpr f32 radius = 10.0f;
    constexpr Vector3 position = {0.0f, 0.0f, 0.0f};
    const Mesh sphere = GenMeshSphere(radius, 64, 64);
    const Model model = LoadModelFromMesh(sphere);
    auto planet_model = std::make_shared<zap::ZapModel>(model);

    planet_model->setPosition(position);
    planet_model->setTint(LIME);

    return Planet{.radius = radius, .position = position, .model = planet_model};
}

/**
* public entry-point
*/

std::shared_ptr<zap::render::Scene> zappy::_create_main_scene(const protocol::GUI_Map &map)
{
    auto scene = std::make_shared<zap::render::Scene>();
    const auto planet = _create_planet(map);

    scene->add(planet.model);
    scene->add(std::make_shared<zap::ZapCamera>());
    return scene;
}
