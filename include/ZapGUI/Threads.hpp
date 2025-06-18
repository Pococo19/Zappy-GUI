/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Threads.hpp
*/

#pragma once

#include <thread>

#ifdef async
    #pragma message("async macro already defined, undefining it")
    #undef async
#endif

#define async(func, ...)                                                                                                                                                 \
    void func##_impl(__VA_ARGS__);                                                                                                                                       \
    template<typename... Args>                                                                                                                                           \
    static inline void func(Args &&...args)                                                                                                                              \
    {                                                                                                                                                                    \
        std::thread([=]() { func##_impl(args...); }).detach();                                                                                                           \
    }                                                                                                                                                                    \
    void func##_impl(__VA_ARGS__)
