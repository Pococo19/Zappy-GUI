/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Context.cpp
*/

#include <ZapGUI/Context.hpp>
#include <ZapGUI/Error.hpp>
#include <ZapGUI/Logger.hpp>
#include <ZapGUI/Macro.hpp>
#include <ZapGUI/Raylib.hpp>
#include <ZapGUI/Render/Loop.hpp>

/**
* public entry point
*/

static void _create_window_context(const Vector2u &size, const std::string &title, const u32 max_framerate)
{
    InitWindow(static_cast<i32>(size._x), static_cast<i32>(size._y), title.c_str());
    SetTargetFPS(static_cast<i32>(max_framerate));
    HideCursor();
}

static void __yield(zap::abstract::GameEngine *engine)
{
    std::unique_ptr<zap::render::Loop> loop = std::make_unique<zap::render::Loop>(engine);

    engine->startup();
    loop->run();
}

i32 zap::context::run(std::unique_ptr<abstract::GameEngine> engine, const Vector2u &size, const std::string &title, const u32 max_framerate)
{
    _create_window_context(size, title, max_framerate);

    static const auto __cleanup = [&]() {
        engine->shutdown();
        engine.reset();
        CloseWindow();
    };

    try {
        __yield(engine.get());
    } catch (const exception::Error &e) {
        logger::error(e);
        __cleanup();
        return ERROR;
    }
    __cleanup();
    return SUCCESS;
}
