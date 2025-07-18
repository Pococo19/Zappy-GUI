/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** RenderLoop.cpp
*/

#include "Loop.hpp"
#include <App/Application.hpp>
#include <ZapGUI/Logger.hpp>
#include <ZapGUI/Raylib.hpp>
#include <ZapGUI/Render/Loop.hpp>

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
        _update();
        _render();
    }
}

/**
* private
*/

void zap::render::Loop::_render() const noexcept
{

    BeginDrawing();
    ClearBackground(BLACK);
    _engine->render();
    DrawText("ESC to leave", 10, 10, 20, DARKGRAY);
    DrawFPS(10, 30);
    EndDrawing();
}

void zap::render::Loop::_update() const noexcept
{
    _engine->update();
}
