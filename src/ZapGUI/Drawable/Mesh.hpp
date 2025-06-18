/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Mesh.hpp
*/

#pragma once

#include <ZapGUI/Raylib.hpp>

#include <ZapGUI/Types.hpp>

#include <vector>

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wmissing-field-initializers"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

namespace zap {

struct ZapMesh {
    public:
        constexpr explicit ZapMesh() noexcept = default;
        explicit ZapMesh(const Mesh &mesh) noexcept;
        constexpr ~ZapMesh() noexcept = default;

        [[nodiscard]] const Mesh &get() const noexcept;
        void clone(const std::vector<f32> &vertices, const std::vector<f32> &normals, const std::vector<f32> &texcoords, const std::vector<u16> &indices);

        void vertexCount(const u64 count) noexcept;
        void triangleCount(const u64 count) noexcept;
        void vertices(const std::vector<Vector3> &vertex) noexcept;

        void upload();

    private:
        Mesh _mesh = {0};
};
}// namespace zap

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif
