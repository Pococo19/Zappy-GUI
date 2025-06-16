/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Maths.hpp
*/

#pragma once

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>

#include <ZapGUI/Types.hpp>

namespace zappy::maths {

/**
* @brief spherical coordinate system: r, θ, φ
*/

/**
 * @brief converts UV coordinates to Vec3 positions on a sphere
 *
 * θ = u × 2π  (azimuthal angle)
 * φ = (0.5 - v) × π  (polar angle)
 * x = r × cosφ × cosθ
 * y = r × sinφ
 * z = r × cosφ × sinθ
 */
static inline const Vector3 to_sphere(const f32 u, const f32 v, const f32 radius)
{
    const f32 theta = u * 2.0f * PI;//<< θ ∈ [0,2π]
    const f32 phi = (0.5f - v) * PI;//<< φ ∈ [-π/2,π/2]

    return {
        radius * cosf(phi) * cosf(theta),//<< x coordinate
        radius * sinf(phi),              //<< y coordinate
        radius * cosf(phi) * sinf(theta) //<< z coordinate
    };
}

}// namespace zappy::maths
