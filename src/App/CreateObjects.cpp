/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** CreateObjects.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>

#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Logger.hpp>

#include <App/Application.hpp>
#include <App/Maths/Maths.hpp>

#include <algorithm>

/**
 * private struct, attributes and constants
 */
struct Planet {
        f32 radius;
        Vector3 position;
        std::shared_ptr<zap::abstract::Drawable> model;
};

struct ResourceMarker {
        std::shared_ptr<zap::ZapModel> model;
        Vector3 position;
        Color color;
};

/**
 * private functions
 */

static constexpr Color _get_color(const zappy::protocol::RessourceType type)
{
    switch (type) {
        case zappy::protocol::FOOD:
            return RED;
        case zappy::protocol::LINEMATE:
            return BLUE;
        case zappy::protocol::DERAUMERE:
            return GREEN;
        case zappy::protocol::SIBUR:
            return YELLOW;
        case zappy::protocol::MENDIANE:
            return PURPLE;
        case zappy::protocol::PHIRAS:
            return ORANGE;
        case zappy::protocol::THYSTAME:
            return PINK;
        default:
            return WHITE;
    }
}

static const Planet _create_planet(const zappy::protocol::GUI_Map &map)
{
    if (map.empty() || map.front().empty()) {
        throw zap::exception::Error("CreatePlanet", "Map is empty or malformed");
    }

    const f32 width = static_cast<f32>(map.front().size());
    const f32 height = static_cast<f32>(map.size());
    const f32 radius = std::max(width, height) / (2.0f * PI);

    constexpr Vector3 position = {0.0f, 0.0f, 0.0f};

    const Mesh sphere = GenMeshSphere(radius, 64, 64);
    const Model model = LoadModelFromMesh(sphere);
    auto planet_model = std::make_shared<zap::ZapModel>(model);

    planet_model->setPosition(position);
    planet_model->setTint(LIME);

    return Planet{.radius = radius, .position = position, .model = std::move(planet_model)};
}

static void _create_resource_marker(const zappy::protocol::GUI_Map &map, f32 planetRadius, std::vector<ResourceMarker> &resources)
{
    if (map.empty() || map.front().empty()) {
        throw zap::exception::Error("CreateResourceMarker", "Map is empty or malformed");
    }

    const u64 width = map.front().size();
    const u64 height = map.size();

    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {

            const f32 u = (static_cast<f32>(x)) / static_cast<f32>(width);
            const f32 v = (static_cast<f32>(y)) / static_cast<f32>(height);
            const Vector3 vec3_position = zappy::maths::to_sphere(u, v, planetRadius);

            /** @brief create marker for each ressource type */
            for (u32 type = 0; type < MAX_RESSOURCES; type++) {

                if (map[y][x][type].quantity > 0) {
                    const Mesh cube = GenMeshCube(0.3f, 0.3f, 0.3f);
                    const auto model = std::make_shared<zap::ZapModel>(LoadModelFromMesh(cube));
                    const Vector3 vec3_offset = Vector3Scale(Vector3Normalize(vec3_position), 0.1f);
                    const Vector3 vec3_final_pos = Vector3Add(vec3_position, vec3_offset);

                    const ResourceMarker marker{.model = model, .position = vec3_final_pos, .color = _get_color(static_cast<zappy::protocol::RessourceType>(type))};

                    resources.push_back(marker);
                }
            }
        }
    }
}

static const std::shared_ptr<zap::ZapCamera> _create_camera(const Planet &planet)
{
    const auto camera = std::make_shared<zap::ZapCamera>();

    camera->setPosition({0.0f, 0.0f, planet.radius * 2.5f});
    camera->setTarget(planet.position);
    return camera;
}

/**
* public entry-point
*/

std::shared_ptr<zap::render::Scene> zappy::_create_main_scene(const protocol::GUI_Map &map)
{
    const auto scene = std::make_shared<zap::render::Scene>();
    const Planet planet = _create_planet(map);

    scene->add(planet.model);

    std::vector<ResourceMarker> resources;
    _create_resource_marker(map, planet.radius, resources);

    for (const auto &resource : resources) {
        resource.model->setPosition(resource.position);
        resource.model->setTint(resource.color);
        scene->add(resource.model);
    }

    scene->add(_create_camera(planet));

    return scene;
}
