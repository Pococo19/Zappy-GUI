/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Context.cpp
*/

#define ZAP_RAYLIB_NO_LOGGING
#define ZAP_USE_RAYLIB_RLGL
#include <ZapGUI/Raylib.hpp>

#include <ZapGUI/Context.hpp>
#include <ZapGUI/Error.hpp>
#include <ZapGUI/Logger.hpp>
#include <ZapGUI/Macro.hpp>
#include <ZapGUI/Render/Loop.hpp>

/**
* public entry point
*/

static inline void _create_window_context(const Vector2u &size, const std::string &title, const u32 max_framerate)
{
#if defined(ZAP_RAYLIB_NO_LOGGING)
    SetTraceLogLevel(LOG_NONE);
#endif

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(static_cast<i32>(size._x), static_cast<i32>(size._y), title.c_str());
    SetTargetFPS(static_cast<i32>(max_framerate));
    DisableCursor();
}

static inline void _yield(zap::abstract::GameEngine *engine)
{
    std::unique_ptr<zap::render::Loop> loop = std::make_unique<zap::render::Loop>(engine);

    engine->startup();
    loop->run();
}

void zap::context::run(std::unique_ptr<abstract::GameEngine> engine, const Vector2u &size, const std::string &title, const u32 max_framerate)
{
    _create_window_context(size, title, max_framerate);

    static const auto _cleanup = [&engine]() {
        engine->shutdown();
        engine.reset();
        CloseWindow();
    };

    std::unique_ptr<render::Loop> loop = std::make_unique<render::Loop>(engine.get());

    try {
        _yield(engine.get());
    } catch (const zap::exception::Error &e) {
        _cleanup();
        throw e;
    }
    _cleanup();
}
