/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** EventCallback.cpp
*/

#include <ZapGUI/Raylib.hpp>

#include <ZapGUI/Event/EventCallback.hpp>

/**
* public
*/

zap::event::EventCallback &zap::event::EventCallback::getInstance()
{
    static EventCallback instance;

    return instance;
}

void zap::event::EventCallback::add(i32 key, Callback callback)
{
    _callbacks.emplace_back(key, std::move(callback));
}

void zap::event::EventCallback::listen() const
{
    for (const auto &[key, callback] : _callbacks) {
        if (IsKeyPressed(key)) {
            callback();
        }
    }
}
