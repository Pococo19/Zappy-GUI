/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Maths.hpp
*/

#pragma once

#include <type_traits>
#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>

#include <ZapGUI/Types.hpp>
#include <algorithm>
#include <random>

// clang-format off
namespace zappy::maths {

/**
 * @brief converts UV coordinates to Vec3 positions on a sphere
 *
 * θ = u × 2π  (longitude, θ ∈ [0,2π])
 * φ = v × π  (latitude, φ ∈ [0,π])
 *
 * x = r × sinφ × cosθ
 * y = r × cosφ
 * z = r × sinφ × sinθ
 */
static const inline Vector3 to_sphere(const Vector2f &uv, const f32 radius)
{
    const f32 theta = uv._x * 2.0f * PI;//<< longitude θ ∈ [0,2π]
    const f32 phi = uv._y * PI;         //<< latitude (θ ∈ π)

    /** @brief cartesian coordinates from spherical coordinates */
    const f32 x = radius * sinf(phi) * cosf(theta);
    const f32 y = radius * cosf(phi);
    const f32 z = radius * sinf(phi) * sinf(theta);

    return Vector3{x, y, z};
}

static inline Vector3 rotation(const Vector3 &position, f32 *out_angle)
{
    constexpr Vector3 center = {0.0f, 0.0f, 0.0f};
    constexpr Vector3 up = {0.0f, 1.0f, 0.0f};
    const Vector3 normalized = Vector3Normalize(Vector3Subtract(position, center));
    const Vector3 axis = Vector3CrossProduct(up, normalized);
    const f32 angle = acosf(Vector3DotProduct(up, normalized));

    if (Vector3Length(axis) > EPSILON) {
        *out_angle = angle * RAD2DEG;
        return {
            axis.x,
            axis.y,
            axis.z,
        };
    }
    *out_angle = 0.0f;
    return {0.0f, 0.0f, 0.0f};
}

/**
* @brief calculates the tile coordinates on a sphere based on a vertex and length
*
* θ = atan2(z, x)
* φ = acos(y / length)
* u = (θ + π) / (2π)
* v = φ / π
*/
static const inline Vector2u get_tiles(const Vector3 &vertex, const f32 length, const Vector2u &width_height)
{
    const Vector3 normalized = Vector3Scale(vertex, 1.0f / length);
    const f32 theta = atan2f(normalized.z, normalized.x);
    const f32 phi = acosf(std::clamp(normalized.y, -1.0f, 1.0f));
    const f32 u = (theta + PI) / (2.0f * PI);
    const f32 v = phi / PI;

    return Vector2u{
        static_cast<u32>(std::clamp(u * static_cast<f32>(width_height._x), 0.0f, static_cast<f32>(width_height._x - 1))),
        static_cast<u32>(std::clamp(v * static_cast<f32>(width_height._y), 0.0f, static_cast<f32>(width_height._y - 1)))
    };
}

/**
* @brief generates a random integer between min and max (inclusive)
*/
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
static inline T random(const T min, const T max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>) {
        /** @brief for integral types (e.g., i32, i64) */
        std::uniform_int_distribution<T> dis(min, max);
        return dis(gen);

    /**
     * WARN: the `else` branch is **REQUIRED** because the first is a `constexpr` if
     **/

    } else {
        /** @brief for floating-point types (e.g., f32, f64) */
        std::uniform_real_distribution<T> dis(min, max);
        return dis(gen);
    }
}

}// namespace zappy::maths
// clang-format on
