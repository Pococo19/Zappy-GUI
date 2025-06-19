/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** CreateObjects.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>

#include <ZapGUI/Drawable/Mesh.hpp>
#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Logger.hpp>

#include <App/Application.hpp>
#include <App/Maths/Maths.hpp>
#include <App/Seed/Create.hpp>
#include <App/Sun/Sun.hpp>

/**
 * private struct, attributes and constants
 */

struct Planet {
        f32 radius;
        Vector3 position;
        std::shared_ptr<zap::abstract::Drawable> model;
};

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
 * @brief create a safe deformed mesh according to GUI_Map (2D Matrix) and a radius
 */
static Mesh _create_safe_deformed_mesh(const zappy::protocol::GUI_Map &map, f32 radius)
{
    const u32 width = static_cast<u32>(map.front().size());
    const u32 height = static_cast<u32>(map.size());

    const i32 subdivisions = static_cast<i32>(std::max(32u, std::max(width * 2, height * 2)));
    const Mesh base_sphere = GenMeshSphere(radius, subdivisions, subdivisions);

    if (base_sphere.vertices == nullptr || base_sphere.vertexCount == 0) {
        TraceLog(LOG_ERROR, "Failed to generate base sphere mesh");
        return base_sphere;
    }

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texcoords;
    std::vector<unsigned short> indices;

    /** @brief avoid reallocating memory multiple times so we massively ALLOCATE */
    vertices.reserve(static_cast<u32>(base_sphere.vertexCount * 3));
    normals.reserve(static_cast<u32>(base_sphere.vertexCount * 3));
    if (base_sphere.texcoords) {
        texcoords.reserve(static_cast<u32>(base_sphere.vertexCount * 2));
    }
    if (base_sphere.indices) {
        indices.reserve(static_cast<u32>(base_sphere.triangleCount * 3));
    }

    /** @brief process each vertex of the base sphere */
    for (u32 i = 0; i < static_cast<u32>(base_sphere.vertexCount); ++i) {
        const Vector3 vertex = {base_sphere.vertices[i * 3], base_sphere.vertices[i * 3 + 1], base_sphere.vertices[i * 3 + 2]};
        const f32 length = Vector3Length(vertex);

        if (length < EPSILON) {
            vertices.push_back(vertex.x);
            vertices.push_back(vertex.y);
            vertices.push_back(vertex.z);
            normals.push_back(0.0f);
            normals.push_back(1.0f);
            normals.push_back(0.0f);
            continue;
        }

        const auto tiles = zappy::maths::get_tiles(vertex, length, {width, height});
        f32 resource_density = 0.0f;

        if (tiles._y < height && tiles._x < width) {
            for (u32 res = 0; res < 7; ++res) {
                resource_density += static_cast<f32>(map[tiles._y][tiles._x][res].quantity);
            }
        }

        const f32 deformation_factor = 1.0f + (resource_density * 0.01f);
        const Vector3 deformed_vertex = Vector3Scale(vertex, deformation_factor);
        vertices.push_back(deformed_vertex.x);
        vertices.push_back(deformed_vertex.y);
        vertices.push_back(deformed_vertex.z);

        const Vector3 normal = Vector3Normalize(deformed_vertex);
        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);
    }

    if (base_sphere.texcoords) {
        for (u32 i = 0; i < static_cast<u32>(base_sphere.vertexCount * 2); ++i) {
            texcoords.push_back(base_sphere.texcoords[i]);
        }
    }

    if (base_sphere.indices) {
        for (u32 i = 0; i < static_cast<u32>(base_sphere.triangleCount * 3); ++i) {
            indices.push_back(base_sphere.indices[i]);
        }
    }

    zap::ZapMesh deformed_mesh(base_sphere);

    deformed_mesh.clone(vertices, normals, texcoords, indices);

    UnloadMesh(base_sphere);
    return deformed_mesh.get();
}

/**
 * @brief create a planet according to the 2D matrix GUI_Map
 */
static const Planet _create_planet(const zappy::protocol::GUI_Map &map)
{
    if (map.empty() || map.front().empty()) {
        throw zap::exception::Error("CreatePlanet", "Map is empty or malformed");
    }

    const f32 width = static_cast<f32>(map.front().size());
    const f32 height = static_cast<f32>(map.size());
    const f32 radius = std::max(width, height) / (2.0f * PI);

    constexpr Vector3 position = {0.0f, 0.0f, 0.0f};

    Mesh deformed_mesh = _create_safe_deformed_mesh(map, radius);

    UploadMesh(&deformed_mesh, false);

    const Model model = LoadModelFromMesh(deformed_mesh);
    auto planet_model = std::make_shared<zap::ZapModel>(model);

    planet_model->setPosition(position);
    planet_model->setTint(LIME);

    return Planet{.radius = radius, .position = position, .model = std::move(planet_model)};
}

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

static const std::shared_ptr<zap::ZapCamera> _create_camera(const Planet &planet)
{
    const auto camera = std::make_shared<zap::ZapCamera>();

    camera->setPosition({0.0f, 0.0f, planet.radius * 2.5f});
    camera->setTarget(planet.position);
    return camera;
}

/**
 * main entry point WARN: do not change the signature
 */
std::shared_ptr<zap::render::Scene> zappy::_create_main_scene(const protocol::GUI_Map &map)
{
    auto scene = std::make_shared<zap::render::Scene>();
    const Planet planet = _create_planet(map);

    scene->add(planet.model);

#if defined(DEBUG)
    std::vector<TileOutline> outlines;
    _create_tile_outlines(map, planet.radius, outlines);

    for (const auto &outline : outlines) {
        outline.model->setTint(outline.color);
        scene->add(outline.model);
    }
#endif

    create::rocks(map, scene, planet.radius + 0.05f);
    create::trees(scene, {static_cast<u32>(map.front().size()), static_cast<u32>(map.size())}, planet.radius);

    auto camera = _create_camera(planet);
    scene->add(camera);

    auto sun = std::make_shared<zappy::Sun>(camera);
    scene->add(sun);

    return scene;
}
