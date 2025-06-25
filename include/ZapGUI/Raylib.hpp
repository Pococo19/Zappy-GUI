/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Raylib.hpp
*/

#pragma once

// clang-format off
#include <ostream>
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wundef"
    #pragma clang diagnostic ignored "-Wmissing-field-initializers"
    #pragma clang diagnostic ignored "-Wswitch-default"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wundef"
    #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    #pragma GCC diagnostic ignored "-Wswitch-default"
#endif
#include <raylib.h>
#if defined ZAP_USE_RAYLIB_MATH
#include <raymath.h>
#endif
#if defined ZAP_USE_GLFW
#include <raylib/src/external/glfw/include/GLFW/glfw3.h>
#endif
#if defined ZAP_USE_RAYLIB_RLGL
#include <raylib/src/rlgl.h>
#endif
#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif
// clang-format on

static inline std::ostream &operator<<(std::ostream &os, const Vector2 &v)
{
    os << "{" << v.x << ", " << v.y << "}";
    return os;
}

static inline std::ostream &operator<<(std::ostream &os, const Vector3 &v)
{
    os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
    return os;
}
