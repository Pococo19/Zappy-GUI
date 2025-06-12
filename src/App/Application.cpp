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
    _client = std::make_unique<zap::Client>(flags.port, flags.hostname);
    _client->connect();
}

static std::unique_ptr<zap::abstract::Drawable> __attribute_maybe_unused__ _create_model(const std::string &obj_path)
{
    return std::make_unique<zap::ZapModel>(obj_path, "assets/textures/");
}

void zappy::Application::init()
{
    addScene("main", _create_main_scene());
}

void zappy::Application::update()
{
    zap::abstract::GameEngine::update();
}
