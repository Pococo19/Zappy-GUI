/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Application.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>

#include <App/Application.hpp>
#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Error.hpp>

/**
* public
*/

zappy::Application::Application(const parser::Flags &flags)
{
    _net = std::make_unique<zap::NetworkClient>(flags.port, flags.hostname);
}

void zappy::Application::init()
{
    addScene("main", _create_main_scene());
}

void zappy::Application::update()
{
    zap::abstract::GameEngine::update();
}
