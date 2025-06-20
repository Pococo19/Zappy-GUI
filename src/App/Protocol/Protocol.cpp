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
static inline std::mutex _data_mutex;

bool zappy::protocol::_ready = false;
zappy::protocol::Data zappy::protocol::_data;

/**
 * protocol functions
 */

zappy::protocol::Data zappy::protocol::getData()
{
    std::lock_guard<std::mutex> lock(_data_mutex);

    return _data;
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

        std::lock_guard<std::mutex> lock(_data_mutex);
        _data.map = std::vector<std::vector<std::array<protocol::Resource, 7>>>(height, std::vector<std::array<protocol::Resource, 7>>(width));
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

        std::array<protocol::Resource, ZAP_MAX_RESOURCES> resources = {};
        for (u8 i = 0; i < ZAP_MAX_RESOURCES; ++i) {
            resources[i].type = static_cast<protocol::ResourceType>(i);
            resources[i].quantity = params[i + 2];
        }

        {
            std::lock_guard<std::mutex> lock(_data_mutex);
            
            if (_data.map.empty()) {
                throw zap::exception::Error("BCT", "Map is not initialized yet. Please ensure 'msz' command was received before 'bct'.");
            }
            
            if (y >= _data.map.size() || x >= _data.map[y].size()) {
                throw zap::exception::Error("BCT", "Coordinates out of bounds: x=", x, ", y=", y, ", map_height=", _data.map.size(), ", map_width=", _data.map.empty() ? 0 : _data.map[0].size());
            }

            _data.map[y][x] = resources;
            ++_received_tiles;
        }

        zap::logger::recv("Received tile ", _received_tiles, "/", _max_tiles);

        if (_received_tiles == _max_tiles) {
            std::lock_guard<std::mutex> lock(_data_mutex);
            zap::logger::debug("All tiles received, map is ready! Map size: ", _data.map.size(), "x", (_data.map.empty() ? 0 : _data.map[0].size()));
            protocol::_ready = true;
        }
    }});

    /** @brief SGT -> [time] */
    protocol::_callbacks.insert({"sgt", [](const std::string &data) -> void
    {
        const auto time = protocol::parse<u32>(data, 1);

        _data.time = time.front();
    }});

    // tna N\n * nbr_teams
    /** @brief TNA -> [team_name] */
    protocol::_callbacks.insert({"tna", [](const std::string &data) -> void
    {
        const auto team_name = protocol::parse<std::string>(data, 1);

        _data.teams.push_back(team_name.front());
    }});

    /** @brief ENW -> [egg_id, player_id, x, y] */
    protocol::_callbacks.insert({"enw", [](const std::string &data) -> void
    {
        const auto params = protocol::parse<std::string>(data, 4);

        if (params.size() < 4) {
            throw zap::exception::Error("ENW", "Invalid number of parameters");
        }

        const std::string &egg_id = params[0];
        const std::string &player_id = params[1];
        const u32 x = static_cast<u32>(std::stoul(params[2]));
        const u32 y = static_cast<u32>(std::stoul(params[3]));

        zap::logger::recv("Egg spawned with ID: ", egg_id, ", Player ID: ", player_id, ", at coordinates (", x, ", ", y, ")");
    }});

    /**
    * @brief set callback for receiving commands from the server
    */
    net->setCallback([](const std::string &line) -> void
    {
        const std::string cmd = line.substr(0, line.find(' '));

        if (protocol::_callbacks.contains(cmd)) {
            const std::string line_without_cmd = std::string(line).substr(cmd.size());

            protocol::_callbacks[cmd](line_without_cmd);
            return;
        }

        throw zap::exception::Error("Protocol", "No callback registered for command: ", cmd);
    });
    // clang-format on

    run_client(net);//<< async function to run the client in a separate thread;
}
