/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Macro.hpp
*/

#pragma once

#define SUCCESS 0
#define ERROR 84

#if defined(_MSC_VER)
    #define RESTRICT __restrict
#elif defined(__GNUC__)
    #define RESTRICT __restrict__
#else
    #define RESTRICT
#endif

#if defined(UNIT_TESTS)
    #define unit_static
#else
    #define unit_static static
#endif

#if defined(DEBUG)
    #define ZAP_VISIBILITY __attribute__((visibility("default")))
#else
    #define ZAP_VISIBILITY __attribute__((visibility("hidden")))
#endif

#define UNUSED __attribute__((unused))

/**
* @brief DEFAULT MACROS
* @details default general macros to avoid magic numbers everywhere
*/

#define ZAP_DEFAULT_WINDOW_SIZE {1920, 1080}

#define ZAP_DEFAULT_MAX_FRAMERATE 120.0

#ifndef ZAP_GUI_VERSION
    #define ZAP_GUI_VERSION "0.0.1"
#endif
