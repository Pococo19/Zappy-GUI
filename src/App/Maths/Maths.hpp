/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Maths.hpp
*/

#pragma once

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>
#include <type_traits>

#include <ZapGUI/Types.hpp>
#include <algorithm>
#include <random>

#define PI_2 (2.f * PI)
#define ALMOST_ONE 0.999999f

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
[[nodiscard]] static const inline Vector3 to_sphere(const Vector2f &uv, const f32 radius)
{
    const f32 theta = uv._x * 2.f * PI;//<< longitude θ ∈ [0,2π]
    const f32 phi = uv._y * PI;         //<< latitude (θ ∈ π)

    /** @brief cartesian coordinates from spherical coordinates */
    const f32 x = radius * sinf(phi) * cosf(theta);
    const f32 y = radius * cosf(phi);
    const f32 z = radius * sinf(phi) * sinf(theta);

    return Vector3{x, y, z};
}

/**
* @brief calculates the position of an orbiting object around a center point
*
* pos = (orbit_radius × cos(time × speed), 0, orbit_radius × sin(time × speed))
*/
[[nodiscard]] static const inline Vector3 orbit_position(const f32 speed, const f32 around_radius, const f32 time, const f32 offset = 4.5f)
{
    const f32 orbit_radius = around_radius * offset + around_radius;

    return {
        orbit_radius * cosf(time * speed),
        0.f,
        (orbit_radius * 0.8f) * sinf(time * speed)
    };
}

/**
 * @brief radius
 */
[[nodiscard]] static inline f32 radius(const u64 w, const u64 h)
{
    const f32 width = static_cast<f32>(w);
    const f32 height = static_cast<f32>(h);

    return std::max(width, height) / (PI_2);
}

/**
 * @brief 2D to 3D
 */
[[nodiscard]] static inline Vector3 to_3D(const Vector2f &pos_2d, const Vector2u &size, const f32 radius)
{
    const Vector2f uv = {pos_2d._x / float(size._x), pos_2d._y / float(size._y)};
    const Vector3 pos = to_sphere(uv, radius);

    return {
        pos.x,
        pos.y,
        pos.z
    };
}

/**
* @brief calculates the rotation axis and angle between two vectors
*
*   axis = up × normalized
*   angle = acos(up ⋅ normalized)
*/
[[nodiscard]] static inline Vector3 rotation(const Vector3 &position, f32 *out_angle, const bool use_up = true)
{
    constexpr Vector3 center = {0.f, 0.f, 0.f};
    constexpr Vector3 up = {0.f, 1.f, 0.f};

    const Vector3 normalized = Vector3Normalize(Vector3Subtract(position, center));
    Vector3 model_up;

    if (use_up) {
        model_up = up;
    } else {
        model_up = {0.f, 0.f, -1.f};
    }

    const Vector3 axis = Vector3CrossProduct(model_up, normalized);
    const f32 angle = acosf(Vector3DotProduct(model_up, normalized));
    const f32 dot = Vector3DotProduct(model_up, normalized);

    if (abs(dot) > ALMOST_ONE) {
        *out_angle = 0.f;
        return {0.f, 0.f, 1.f};
    }
    if (Vector3Length(axis) > EPSILON) {
        *out_angle = angle * RAD2DEG;
        return Vector3Normalize(axis);
    }
    *out_angle = 0.f;
    return {0.f, 0.f, 1.f};
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
    const Vector3 normalized = Vector3Scale(vertex, 1.f / length);
    const f32 theta = atan2f(normalized.z, normalized.x);
    const f32 phi = acosf(std::clamp(normalized.y, -1.f, 1.f));
    const f32 u = (theta + PI) / (2.f * PI);
    const f32 v = phi / PI;

    return Vector2u{
        static_cast<u32>(std::clamp(u * static_cast<f32>(width_height._x), 0.f, static_cast<f32>(width_height._x - 1))),
        static_cast<u32>(std::clamp(v * static_cast<f32>(width_height._y), 0.f, static_cast<f32>(width_height._y - 1)))
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
