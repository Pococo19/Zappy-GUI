/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Mesh.cpp
*/

#include <ZapGUI/Drawable/Mesh.hpp>

/**
* public
*/

/**
* @brief Constructs a ZapMesh from an existing Raylib Mesh.
*/
zap::ZapMesh::ZapMesh(const Mesh &mesh) noexcept
{
    _mesh.vertexCount = mesh.vertexCount;
    _mesh.triangleCount = mesh.triangleCount;
}

/**
* @brief Returns a constant reference to the underlying Raylib Mesh.
*/
const Mesh &zap::ZapMesh::get() const noexcept
{
    return _mesh;
}

/**
* @brief Clones the provided vertex, normal, texture coordinate, and index data into the ZapMesh.
*/
void zap::ZapMesh::clone(const std::vector<f32> &vertices, const std::vector<f32> &normals, const std::vector<f32> &texcoords, const std::vector<u16> &indices)
{
    if (!vertices.empty()) {
        _mesh.vertices = static_cast<f32 *>(MemAlloc(static_cast<u32>(vertices.size() * sizeof(f32))));
        if (_mesh.vertices) {
            std::copy(vertices.begin(), vertices.end(), _mesh.vertices);
        }
    }
    if (!normals.empty()) {
        _mesh.normals = static_cast<f32 *>(MemAlloc(static_cast<u32>(normals.size() * sizeof(f32))));
        if (_mesh.normals) {
            std::copy(normals.begin(), normals.end(), _mesh.normals);
        }
    }
    if (!texcoords.empty()) {
        _mesh.texcoords = static_cast<f32 *>(MemAlloc(static_cast<u32>(texcoords.size() * sizeof(f32))));
        if (_mesh.texcoords) {
            std::copy(texcoords.begin(), texcoords.end(), _mesh.texcoords);
        }
    }
    if (!indices.empty()) {
        _mesh.indices = static_cast<u16 *>(MemAlloc(static_cast<u32>(indices.size() * sizeof(u16))));
        if (_mesh.indices) {
            std::copy(indices.begin(), indices.end(), _mesh.indices);
        }
    }
}

void zap::ZapMesh::upload()
{
    if (_mesh.vertices) {
        UploadMesh(&_mesh, false);
    }
}

/**
* setters
*/

void zap::ZapMesh::vertexCount(const u64 count) noexcept
{
    _mesh.vertexCount = static_cast<i32>(count);
}

void zap::ZapMesh::triangleCount(const u64 count) noexcept
{
    _mesh.triangleCount = static_cast<i32>(count);
}

void zap::ZapMesh::vertices(const std::vector<Vector3> &vertex) noexcept
{
    const u32 size = static_cast<u32>(vertex.size() * 3 * sizeof(f32));

    _mesh.vertices = static_cast<f32 *>(MemAlloc(size));
    for (u32 i = 0; i < vertex.size(); ++i) {
        _mesh.vertices[i * 3] = vertex[i].x;
        _mesh.vertices[i * 3 + 1] = vertex[i].y;
        _mesh.vertices[i * 3 + 2] = vertex[i].z;
    }
}
