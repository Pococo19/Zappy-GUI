/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Create.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>

#include <ZapGUI/Drawable/Mesh.hpp>
#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Logger.hpp>

#include <App/Application.hpp>
#include <App/Maths/Maths.hpp>
#include <App/Seed/Create.hpp>
#include <App/Stars/Planet.hpp>
#include <App/Stars/Sun.hpp>

/**
 * private struct, attributes and constants
 */

#if defined(DEBUG)
struct TileOutline {
        std::shared_ptr<zap::ZapModel> model;
        Vector3 center;
        Color color;
};
#endif

/**
 * private functions
 */

/**
 * @brief create tile outliness only if `DEBUG` preprocessor is catch'd
 */
#if defined(DEBUG)

typedef enum { TILE_EDGE_BOTTOM = 0, TILE_EDGE_RIGHT, TILE_EDGE_TOP, TILE_EDGE_LEFT } TileEdge;

/**
 * @brief get the UV coordinates for a tile edge based on its position and size
 */
static const Vector2f _get_tiles_uv(const u32 edge, const Vector2u &size, const float t, const Vector2u &pos)
{
    float u, v;

    switch (edge) {
        case TILE_EDGE_BOTTOM:
            u = (static_cast<f32>(pos._x) + t) / static_cast<f32>(size._x);
            v = static_cast<f32>(pos._y) / static_cast<f32>(size._y);
            break;
        case TILE_EDGE_RIGHT:
            u = static_cast<f32>(pos._x + 1) / static_cast<f32>(size._x);
            v = (static_cast<f32>(pos._y) + t) / static_cast<f32>(size._y);
            break;
        case TILE_EDGE_TOP:
            u = (static_cast<f32>(pos._x + 1) - t) / static_cast<f32>(size._x);
            v = static_cast<f32>(pos._y + 1) / static_cast<f32>(size._y);
            break;
        case TILE_EDGE_LEFT:
            u = static_cast<f32>(pos._x) / static_cast<f32>(size._x);
            v = (static_cast<f32>(pos._y + 1) - t) / static_cast<f32>(size._y);
            break;
        default:
            u = static_cast<f32>(pos._x);
            v = static_cast<f32>(pos._y);
            break;
    }
    return {u, v};
}

static const Mesh _create_outline_mesh(const std::vector<Vector3> &outline_points)
{
    zap::ZapMesh mesh;

    mesh.vertexCount(outline_points.size());
    mesh.triangleCount(0);
    mesh.vertices(outline_points);
    mesh.upload();
    return mesh.get();
}

static constexpr Color _get_outline_color(const f32 resource_density)
{
    if (resource_density > 2.0f) {
        return YELLOW;
    } else if (resource_density > 1.0f) {
        return ORANGE;
    } else if (resource_density > 0.0f) {
        return MAGENTA;
    }
    return WHITE;
}

static void _create_tile_outlines(const zappy::protocol::GUI_Map &map, const f32 radius, std::vector<TileOutline> &outlines)
{
    if (map.empty() || map.front().empty()) {
        return;
    }

    const u32 width = static_cast<u32>(map.front().size());
    const u32 height = static_cast<u32>(map.size());

    for (u32 y = 0; y < height; ++y) {
        for (u32 x = 0; x < width; ++x) {

            const u32 outline_resolution = 6;
            std::vector<Vector3> outline_points;
            f32 resource_density = 0.0f;

            outline_points.reserve(outline_resolution * 4);
            for (u32 res = 0; res < 7; ++res) {
                resource_density += static_cast<f32>(map[y][x][res].quantity);
            }

            const f32 deformed_radius = radius * (1.0f + resource_density * 0.01f);

            for (u32 edge = 0; edge < 4; ++edge) {
                for (u32 point = 0; point < outline_resolution; ++point) {
                    const f32 t = static_cast<f32>(point) / static_cast<f32>(outline_resolution);
                    const Vector2f uv = _get_tiles_uv(edge, {width, height}, t, {x, y});
                    const Vector3 sphere_pos = zappy::maths::to_sphere(uv, deformed_radius);
                    constexpr f32 TILE_OUTLINE_OFFSET = 0.005f;
                    const Vector3 offset = Vector3Scale(Vector3Normalize(sphere_pos), TILE_OUTLINE_OFFSET);

                    outline_points.push_back(Vector3Add(sphere_pos, offset));
                }
            }

            if (outline_points.empty()) {
                continue;
            }

            const Mesh outline_mesh = _create_outline_mesh(outline_points);
            const auto outline_model = std::make_shared<zap::ZapModel>(LoadModelFromMesh(outline_mesh));

            const f32 center_u = (static_cast<f32>(x) + 0.5f) / static_cast<f32>(width);
            const f32 center_v = (static_cast<f32>(y) + 0.5f) / static_cast<f32>(height);
            const Vector3 center = zappy::maths::to_sphere({center_u, center_v}, deformed_radius);

            const TileOutline outline{.model = outline_model, .center = center, .color = _get_outline_color(resource_density)};

            outlines.push_back(outline);
        }
    }
}
#endif

/**
 * main entry point WARN: do not change the signature
 */
std::shared_ptr<zap::render::Scene> zappy::_create_main_scene(const protocol::Data &data)
{
    auto scene = std::make_shared<zap::render::Scene>();
    auto camera = std::make_shared<zap::ZapCamera>();
    auto planet = std::make_shared<zappy::Planet>(data.map, camera);
    const f32 planet_radius = planet->getRadius();
    const Vector3 planet_position = planet->getPosition();

#if defined(DEBUG)
    std::vector<TileOutline> outlines;
    _create_tile_outlines(map, planet_radius, outlines);

    for (const auto &outline : outlines) {
        outline.model->setTint(outline.color);
        scene->add(outline.model);
    }
#endif
    camera->setPosition({0.0f, 0.0f, planet_radius * 2.5f});
    camera->setTarget(planet_position);

    scene->add(camera);
    planet->setCamera(camera);
    scene->add(planet);

    create::rocks(data.map, scene, planet_radius + 0.05f);
    create::trees(scene, {static_cast<u32>(data.map.front().size()), static_cast<u32>(data.map.size())}, planet_radius);
    create::sun(scene, camera, planet);

    return scene;
}
