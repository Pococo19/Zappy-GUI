/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Context.hpp
*/

#pragma once

#include <ZapGUI/Engine/GameEngine.hpp>
#include <ZapGUI/Types.hpp>

#include <string>

namespace zap::context {

[[nodiscard]] i32 run(std::unique_ptr<abstract::GameEngine> engine, const Vector2u &size, const std::string &title = "Zappy-GUI", const u32 max_framerate = 120);

}
