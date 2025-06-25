/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Zappy.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <App/Maths/Maths.hpp>
#include <App/Stars/Zappy.hpp>

#include <ZapGUI/Drawable/Mesh.hpp>
#include <ZapGUI/Filename.hpp>

/**
* public
*/

zappy::Zappy::Zappy(const protocol::GUI_Map &map, std::shared_ptr<zap::ZapCamera> camera) : BasePlanet(camera)
{
    _init(map);
    _model->setShader(_shader);
    setColor({0.2f, 0.8f, 0.3f});
}

/**
 * setters
 */

void zappy::Zappy::setCamera(std::shared_ptr<zap::ZapCamera> camera)
{
    _camera = std::move(camera);
}

/**
 * static private helper
 */

/**
 * @brief create a safe deformed mesh according to GUI_Map (2D Matrix) and a radius
 * Enhanced with better texture coordinates for planet surface
 */
static Mesh _create_deformed_mesh(const zappy::protocol::GUI_Map &map, const f32 radius)
{
    const u32 width = static_cast<u32>(map.front().size());
    const u32 height = static_cast<u32>(map.size());

    const i32 subdivisions = static_cast<i32>(std::max(64u, std::max(width * 2, height * 2)));// Higher subdivisions for better lighting
    const Mesh base_sphere = GenMeshSphere(radius, subdivisions, subdivisions);

    if (base_sphere.vertices == nullptr || base_sphere.vertexCount == 0) {
        return base_sphere;
    }

    std::vector<f32> vertices;
    std::vector<f32> normals;
    std::vector<f32> texcoords;
    std::vector<unsigned short> indices;

    /** @brief reserve memory */
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

        f32 resource_density = 0.0f;

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
* private
*/

void zappy::Zappy::_init(const protocol::GUI_Map &map)
{
    constexpr Vector3 position = {0.0f, 0.0f, 0.0f};

    if (map.empty() || map.front().empty()) {
        return;
    }

    _radius = maths::radius(map.front().size(), map.size());

    Mesh deformed_mesh = _create_deformed_mesh(map, _radius);
    UploadMesh(&deformed_mesh, false);

    const Model model = LoadModelFromMesh(deformed_mesh);

    _model = std::make_shared<zap::ZapModel>(model);
    _model->setPosition(position);
    _rotation = 0.0f;
}
