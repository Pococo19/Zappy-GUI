/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** PlayerManager.hpp
*/

#pragma once

#include <App/AI/Player.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>

namespace zappy::ai {

static std::mutex _player_map_mutex;
static std::unordered_map<std::string, std::shared_ptr<Player>> _player_map;

}// namespace zappy::ai
