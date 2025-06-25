/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Threads.hpp
*/

#pragma once

#include "ZapGUI/Render/Scene.hpp"
#include <ZapGUI/NonCopyable.hpp>
#include <functional>
#include <queue>
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

namespace zap::thread {

class Queue final : public abstract::NonCopyable
{
    public:
        void push(std::function<void()> task);
        void push(std::function<void(render::Scene *scene)> task);

        void execute();
        void consume(render::Scene *scene);

        static Queue &getInstance();

    private:
        std::mutex _mutex;
        std::queue<std::function<void()>> _tasks;
        std::queue<std::function<void(render::Scene *scene)>> _scene_tasks;
};
}// namespace zap::thread
