/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Protocol.hpp
*/

#pragma once

#include <ZapGUI/Network/NetworkClient.hpp>

#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace zappy::protocol {

#define ZAP_MAX_RESOURCES 7

// clang-format off
enum ResourceType {
    UNKNOWN = -1,
    FOOD = 0,
    LINEMATE = 1,
    DERAUMERE = 2,
    SIBUR = 3,
    MENDIANE = 4,
    PHIRAS = 5,
    THYSTAME = 6
};

struct Resource {
    ResourceType type = UNKNOWN;
    u32 quantity = 0;
};

// clang-format on

using GUI_Map = std::vector<std::vector<std::array<Resource, ZAP_MAX_RESOURCES>>>;

struct Data {
        GUI_Map map;
        u32 time;
        std::vector<std::string> teams;
};

extern bool _ready;
extern Data _data;

#if defined(await)
    #pragma message("`await` macro is already defined, re-defining it.")
    #undef await
#endif
#define await                                                                                                                                                            \
    while (!zappy::protocol::_ready) {                                                                                                                                   \
        std::this_thread::sleep_for(std::chrono::milliseconds(10));                                                                                                      \
    }

void init(std::shared_ptr<zap::NetworkClient> client);
Data getData();

}// namespace zappy::protocol
