/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Raylib.hpp
*/

#pragma once

// clang-format off
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wundef"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wundef"
#endif
#include <raylib.h>
#if defined ZAP_USE_RAYLIB_MATH
#include <raymath.h>
#endif
#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif
// clang-format on
