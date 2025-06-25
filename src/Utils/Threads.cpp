/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Threads.cpp
*/

#include <ZapGUI/Threads.hpp>

/**
* public
*/

void zap::thread::Queue::push(std::function<void()> task)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _tasks.push(std::move(task));
}

void zap::thread::Queue::push(std::function<void(zap::render::Scene *scene)> task)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _scene_tasks.push(std::move(task));
}

void zap::thread::Queue::execute()
{
    std::queue<std::function<void()>> local;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        std::swap(local, _tasks);
    }

    while (!local.empty()) {
        local.front()();
        local.pop();
    }
}

void zap::thread::Queue::consume(zap::render::Scene *scene)
{
    std::queue<std::function<void(zap::render::Scene * scene)>> local;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        std::swap(local, _scene_tasks);
    }

    while (!local.empty()) {
        local.front()(scene);
        local.pop();
    }
}

zap::thread::Queue &zap::thread::Queue::getInstance()
{
    static zap::thread::Queue instance;

    return instance;
}
