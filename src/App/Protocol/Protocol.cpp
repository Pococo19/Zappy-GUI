/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Protocol.cpp
*/

#include <App/Protocol/Protocol.hpp>

#include <ZapGUI/Error.hpp>
#include <ZapGUI/Logger.hpp>
#include <ZapGUI/Threads.hpp>

/**
 * async function to run the client in a separate thread
 */

async(run_client, std::shared_ptr<zap::NetworkClient> net)
{
    net->start();
}

/**
 * private thread-safe declarations
 */

static inline u32 _max_tiles = 0;
static inline u32 _received_tiles = 0;
static inline std::mutex _map_mutex;

bool zappy::protocol::_ready = false;
zappy::protocol::GUI_Map zappy::protocol::_map;

/**
 * protocol functions
 */

zappy::protocol::GUI_Map zappy::protocol::getMap()
{
    std::lock_guard<std::mutex> lock(_map_mutex);

    return _map;
}

/**
* @brief deklaratywny protokół serwer-klient blyat
* @details to jest inteligentne kurwa
*/
void zappy::protocol::init(std::shared_ptr<zap::NetworkClient> net)
{
    _callbacks.clear();

    // clang-format off
    /**
    * @brief WELCOME -> GRAPHIC
    */
    protocol::_callbacks.insert({"WELCOME", [net](const std::string UNUSED &data) -> void
    {
        net->send("GRAPHIC\n");
    }});

    /**
    * @brief MSZ -> [x, y]
    */
    protocol::_callbacks.insert({"msz", [](const std::string &data) -> void
    {
        const auto size = protocol::parse<u32>(data, 3);
        const u32 width = size[0];
        const u32 height = size[1];

        zap::logger::debug("Initializing map with dimensions: ", width, "x", height);

        std::lock_guard<std::mutex> lock(_map_mutex);
        _map = std::vector<std::vector<std::array<protocol::Ressource, 7>>>(height, std::vector<std::array<protocol::Ressource, 7>>(width));
        _received_tiles = 0;
        _max_tiles = width * height;
        _ready = false;

        zap::logger::debug("Map initialized, expecting ", _max_tiles, " tiles");
    }});

    /**
    * @brief BCT -> [x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame]
    */
    protocol::_callbacks.insert({"bct", [](const std::string &data) -> void
    {
        const auto params = protocol::parse<u32>(data, 9);

        if (params.size() < 9) {
            throw zap::exception::Error("BCT", "Invalid number of parameters");
        }

        const u32 x = params[0];
        const u32 y = params[1];

        std::array<protocol::Ressource, 7> ressources = {};
        for (u8 i = 0; i < 7; ++i) {
            ressources[i].type = static_cast<protocol::RessourceType>(i);
            ressources[i].quantity = params[i + 2];
        }

        {
            std::lock_guard<std::mutex> lock(_map_mutex);
            
            if (_map.empty()) {
                throw zap::exception::Error("BCT", "Map is not initialized yet. Please ensure 'msz' command was received before 'bct'.");
            }
            
            if (y >= _map.size() || x >= _map[y].size()) {
                throw zap::exception::Error("BCT", "Coordinates out of bounds: x=", x, ", y=", y, ", map_height=", _map.size(), ", map_width=", _map.empty() ? 0 : _map[0].size());
            }

            _map[y][x] = ressources;
            ++_received_tiles;
        }

        zap::logger::recv("Received tile ", _received_tiles, "/", _max_tiles);

        if (_received_tiles == _max_tiles) {
            std::lock_guard<std::mutex> lock(_map_mutex);
            zap::logger::debug("All tiles received, map is ready! Map size: ", _map.size(), "x", (_map.empty() ? 0 : _map[0].size()));
            protocol::_ready = true;
        }
    }});

    /**
    * @brief set callback for receiving commands from the server
    */
    net->setCallback([](const std::string &line) -> void
    {
        const std::string cmd = line.substr(0, line.find(' '));

        if (protocol::_callbacks.contains(cmd)) {
            const std::string line_without_cmd = std::string(line).substr(cmd.size());

            if (!protocol::_callbacks.contains(cmd)) {
                throw zap::exception::Error("Protocol", "No callback registered for command: ", cmd);
            }

            protocol::_callbacks[cmd](line_without_cmd);
        }
    });
    // clang-format on

    run_client(net);//<< async function to run the client in a separate thread;
}
