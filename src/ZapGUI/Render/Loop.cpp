/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** RenderLoop.cpp
*/

#include <ZapGUI/Raylib.hpp>
#include <ZapGUI/Render/Loop.hpp>
#include <ZapGUI/Network/Client.hpp>
#include <ZapGUI/Logger.hpp>

/**
* public
*/

zap::render::Loop::Loop(abstract::RenderEngine *engine) noexcept : _engine(engine)
{
    /* __ctor__ */
}

void zap::render::Loop::run() const noexcept
{
    zap::Client client("10.74.253.72", 8000);
    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to server." << std::endl;
    }

    while (!WindowShouldClose()) {
        client.sendMessage("Hello from GUI!");
        _render();
    }
    client.closeSock();
}

/**
* private
*/

void zap::render::Loop::_render() const noexcept
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    _engine->render();
    DrawText("ESC to leave", 10, 10, 20, DARKGRAY);
    EndDrawing();
}
