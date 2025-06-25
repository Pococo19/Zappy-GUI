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

zap::thread::Queue &zap::thread::Queue::getInstance()
{
    static zap::thread::Queue instance;

    return instance;
}

void zap::thread::Queue::push(std::function<void()> task)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _tasks.push(std::move(task));
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

/**
* private
*/
