/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** RenderLoop.cpp
*/

#include <ZapGUI/Raylib.hpp>
#include <ZapGUI/Render/Loop.hpp>
#include <ZapGUI/Logger.hpp>
#include <App/Application.hpp>

/**
* public
*/

zap::render::Loop::Loop(abstract::RenderEngine *engine) noexcept : _engine(engine)
{
    /* __ctor__ */
}

void zap::render::Loop::run() const noexcept
{
    while (!WindowShouldClose()) {
        _render();
    }
}

/**
* private
*/

void zap::render::Loop::_render() const noexcept
{

    // std::string response = _client->receiveMessage();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    _engine->render();
    _engine->update();
    DrawText("ESC to leave", 10, 10, 20, DARKGRAY);
    EndDrawing();
}
