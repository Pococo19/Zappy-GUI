/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Protocol.cpp
*/

#ifndef ZAP_USE_RAYLIB_MATH
    #define ZAP_USE_RAYLIB_MATH
    #include <string>
#endif

#include <App/AI/PlayerManager.hpp>
#include <App/Protocol/Callback.hpp>
#include <App/Seed/Create.hpp>

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
 * private declarations
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
    auto &callback = Callback::getInstance();

    callback.clear();

    ///////////////////////////////////////////////////////////////////////////////////////////////

    /**
    * @brief WELCOME -> GRAPHIC
    */
    callback.add("WELCOME", [net](const std::string UNUSED &data) -> void {
        zap::logger::debug("Received WELCOME command, sending GRAPHIC");
        net->send("GRAPHIC\n");
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    /**
    * @brief MSZ -> [x, y]
    */
    callback.add("msz", [](const std::string &data) -> void {
        const auto size = protocol::parse<u32>(data, 2);
        const u32 width = size[0];
        const u32 height = size[1];
        std::lock_guard<std::mutex> lock(_data_mutex);

        zap::logger::debug("Initializing map with dimensions: ", width, "x", height);
        _data.map = std::vector<std::vector<std::array<protocol::Resource, 7>>>(height, std::vector<std::array<protocol::Resource, 7>>(width));
        _received_tiles = 0;
        _max_tiles = width * height;
        _ready = false;
        zap::logger::debug("Map initialized, expecting ", _max_tiles, " tiles");
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    /**
    * @brief BCT -> [x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame]
    */
    callback.add("bct", [](const std::string &data) -> void {
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
                throw zap::exception::Error("BCT", "Coordinates out of bounds: x=", x, ", y=", y, ", map_height=", _data.map.size(),
                    ", map_width=", _data.map.empty() ? 0 : _data.map[0].size());
            }
            _data.map[y][x] = resources;
            ++_received_tiles;
        }

        zap::logger::recv("Received tile ", _received_tiles, "/", _max_tiles);

        if (_received_tiles == _max_tiles) {
            std::lock_guard<std::mutex> lock(_data_mutex);
            zap::logger::debug("All tiles received, map is ready! Map size: ", _data.map.size(), "x", (_data.map.empty() ? 0 : _data.map[0].size()));
            zappy::protocol::_ready = true;
        }
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    /** @brief SGT -> [time] */
    callback.add("sgt", [](const std::string &data) -> void {
        const auto time = protocol::parse<u32>(data, 1);

        if (time.size() < 1) {
            throw zap::exception::Error("SGT", "Invalid number of parameters");
        }

        std::lock_guard<std::mutex> lock(_data_mutex);
        _data.time = time.front();
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    /** @brief TNA -> [team_name] */
    callback.add("tna", [](const std::string &data) -> void {
        const auto team_name = protocol::parse<std::string>(data, 1);

        if (team_name.size() < 1) {
            throw zap::exception::Error("TNA", "Invalid number of parameters");
        }

        std::lock_guard<std::mutex> lock(_data_mutex);
        _data.teams.push_back(team_name.front());
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    /** @brief ENW -> [egg_id, player_id, x, y] */
    callback.add("enw", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 4);

        if (params.size() < 4) {
            throw zap::exception::Error("ENW", "Invalid number of parameters");
        }

        const std::string &egg_id = params[0];
        const std::string &player_id = params[1];
        const u32 x = static_cast<u32>(std::stoul(params[2]));
        const u32 y = static_cast<u32>(std::stoul(params[3]));

        zap::logger::recv("Egg spawned with ID: ", egg_id, ", Player ID: ", player_id, ", at coordinates (", x, ", ", y, ")");
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    protocol::Callback::getInstance().add("pnw", [](const std::string &data) -> void {
        if (!protocol::_ready) {
            await
        }

        const auto params = protocol::parse<std::string>(data, 6);

        if (params.size() < 6) {
            return;
        }

        f32 angle;

        const u32 size_x = static_cast<u32>(_data.map.size());
        const u32 size_y = static_cast<u32>(_data.map[0].size());
        const f32 radius = maths::radius(size_x, size_y);

        const std::string id = params[0];
        const Vector2f base = {std::stof(params[1]), std::stof(params[2])};
        const Vector3 scale = create::get_scale(radius, size_x, size_y, 500.f);
        const Vector3 pos = maths::to_3D(base, {size_x, size_y}, radius);
        const Vector3 r = maths::rotation(pos, &angle, false);

        ///////////////////////////////////////////////////////////////////////////////////////////////

        zap::thread::Queue::getInstance().push([id, pos, scale, r, angle](zap::render::Scene *scene) {
            const auto player = std::make_shared<zappy::ai::Player>(id);

            player->setPosition(pos);
            player->setScale(scale);
            player->setRotationAxis(r, angle);
            ai::_player_map.insert({id, player});
            scene->add(player);
        });

        ///////////////////////////////////////////////////////////////////////////////////////////////
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("ppo", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 4);

        if (params.size() < 4) {
            return;
        }
        if (ai::_player_map.find(params[0]) == ai::_player_map.end()) {
            return;
        }
        f32 angle;

        const std::string &id = params[0];
        const u32 size_x = static_cast<u32>(_data.map.size());
        const u32 size_y = static_cast<u32>(_data.map[0].size());
        const Vector2f base = {std::stof(params[1]), std::stof(params[2])};
        const Vector3 pos = maths::to_3D(base, {size_x, size_y}, maths::radius(size_x, size_y));
        const Vector3 r = maths::rotation(pos, &angle, false);
        // const i8 orientation = static_cast<i8>(std::stoi(params[3]));

        zap::thread::Queue::getInstance().push([id, pos, r, angle]() {
            ai::_player_map.at(id)->setPosition(pos);
            ai::_player_map.at(id)->setRotationAxis(r, angle);
            ai::_player_map.at(id)->setAnimation(zappy::ai::Player::Animation::INCANTATION);
            // ai::_player_map.at(id)->setOrientation(orientation);
        });
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("pin", [](const std::string UNUSED &data) -> void {
        /* __ pin ___ */
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("pex", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 1);

        if (params.size() < 1) {
            return;
        }
        const std::string &id = params[0];

        zap::thread::Queue::getInstance().push([id](zap::render::Scene *scene) {
            if (ai::_player_map.find(id) == ai::_player_map.end()) {
                return;
            }
            scene->remove(ai::_player_map.at(id).get());
            ai::_player_map.erase(id);
        });
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("pbc", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 1);

        if (params.size() < 1) {
            return;
        }
        const std::string &id = params[0];

        zap::logger::recv("Player ", id, " broadcasted a message");
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////
    
    callback.add("pic", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 5);

        if (params.size() < 5) {
            return;
        }
        const std::string &id = params[0];
        
         zap::thread::Queue::getInstance().push([id]() {
            ai::_player_map.at(id)->setAnimation(zappy::ai::Player::Animation::DEATH);
        });

    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("pie", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 3);

        if (params.size() < 3) {
            return;
        }

        const u32 x = static_cast<u32>(std::stoi(params[0]));
        const u32 y = static_cast<u32>(std::stoi(params[1]));
        const bool success = (params[2] == "1");

        zap::logger::recv("Incantation ended at (", x, ", ", y, ") with result: ", success ? "SUCCESS" : "FAILURE");

        zap::thread::Queue::getInstance().push([x, y, success]() {
        });
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("plv", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 2);

        if (params.size() < 2) {
            return;
        }

        const std::string &id = params[0];
        const u32 level = static_cast<u32>(std::stoi(params[1]));

        if (ai::_player_map.find(id) == ai::_player_map.end()) {
            return;
        }

        zap::thread::Queue::getInstance().push([id, level]() {
            // ai::_player_map.at(id)->setLevel(level);
            zap::logger::recv("Player ", id, " leveled up to ", level);
        });
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("ebo", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 1);

        if (params.size() < 1) {
            return;
        }

        const std::string &egg_id = params[0];

        zap::logger::recv("Egg ", egg_id, " has hatched");

        // zap::thread::Queue::getInstance().push([egg_id]() {
        //     // zap::render::Egg::remove(egg_id);
        // });
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("edi", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 1);

        if (params.size() < 1) {
            return;
        }

        const std::string &egg_id = params[0];

        zap::logger::recv("Egg ", egg_id, " has died");

        // zap::thread::Queue::getInstance().push([egg_id]() {
        //     // zap::render::Egg::remove(egg_id);
        // });
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("pdi", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 1);

        if (params.size() < 1) {
            return;
        }

        const std::string &id = params[0];

        zap::logger::recv("Player ", id, " has died");

        zap::thread::Queue::getInstance().push([id](zap::render::Scene *scene) {
            if (ai::_player_map.find(id) == ai::_player_map.end()) {
                return;
            }
            scene->remove(ai::_player_map.at(id).get());
            ai::_player_map.erase(id);
        });
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("pgt", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 2);

        if (params.size() < 2) {
            return;
        }

        const std::string &id = params[0];
        const u32 resource_id = static_cast<u32>(std::stoi(params[1]));

        zap::logger::recv("Player ", id, " picked up resource #", resource_id);

        // zap::thread::Queue::getInstance().push([id, resource_id]() {
        // });
    });

    ///////////////////////////////////////////////////////////////////////////////////////////////

    callback.add("pdr", [](const std::string &data) -> void {
        const auto params = protocol::parse<std::string>(data, 2);

        if (params.size() < 2) {
            return;
        }

        const std::string &id = params[0];
        const u32 resource_id = static_cast<u32>(std::stoi(params[1]));

        zap::logger::recv("Player ", id, " dropped resource #", resource_id);

        // zap::thread::Queue::getInstance().push([id, resource_id]() {
        // });
    });
    
    ///////////////////////////////////////////////////////////////////////////////////////////////

    /**
    * @brief set callback for receiving commands from the server
    */
    net->setCallback([](const std::string &line) -> void {
        const std::string cmd = line.substr(0, line.find(' '));
        const std::string line_without_cmd = std::string(line).substr(cmd.size());

        Callback::getInstance().call(cmd, line_without_cmd);
    });

    run_client(net);//<< async function to run the client in a separate thread;
}
