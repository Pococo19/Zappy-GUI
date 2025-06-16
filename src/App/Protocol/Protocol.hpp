/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Protocol.hpp
*/

#pragma once

#include <ZapGUI/Network/NetworkClient.hpp>
#include <ZapGUI/Types.hpp>

#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <vector>

namespace zappy::protocol {

// clang-format off
enum RessourceType {
    UNKNOWN = -1,
    FOOD = 0,
    LINEMATE = 1,
    DERAUMERE = 2,
    SIBUR = 3,
    MENDIANE = 4,
    PHIRAS = 5,
    THYSTAME = 6
};

struct Ressource {
    RessourceType type = UNKNOWN;
    u32 quantity = 0;
};
// clang-format on

template<typename T>
const std::vector<T> parse(const std::string_view line, const u32 expected_count)
{
    std::istringstream iss{std::string(line)};
    std::vector<T> result;
    std::string token;

    result.reserve(expected_count);

    while (iss >> token && result.size() < expected_count) {
        if constexpr (std::is_same_v<T, i32>) {
            result.push_back(static_cast<i32>(std::stoi(token)));
        } else if constexpr (std::is_same_v<T, u32>) {
            result.push_back(static_cast<u32>(std::stoi(token)));
        } else {
            result.push_back(static_cast<T>(token));
        }
    }

    return result;
}

using GUI_Map = std::vector<std::vector<std::array<Ressource, 7>>>;
using ParserFunc = std::function<void(const std::string &)>;

extern bool _ready;
extern GUI_Map _map;
static inline std::unordered_map<std::string, ParserFunc> _callbacks;
static inline std::thread _network_thread;

#define await                                                                                                                                                            \
    while (!zappy::protocol::_ready) {                                                                                                                                   \
        std::this_thread::sleep_for(std::chrono::milliseconds(10));                                                                                                      \
    }

void init(std::shared_ptr<zap::NetworkClient> client);
void stop();

GUI_Map getMap();

}// namespace zappy::protocol
