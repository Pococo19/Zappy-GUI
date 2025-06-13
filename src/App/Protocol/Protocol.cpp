/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Protocol.cpp
*/

#include <App/Protocol/Protocol.hpp>
#include <ZapGUI/Logger.hpp>

#include <ZapGUI/Error.hpp>

void zappy::protocol::stop()
{
    if (_network_thread.joinable()) {
        _network_thread.join();
    }
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
        _map = std::vector<std::vector<std::array<protocol::Ressource, 7>>>(size.front(), std::vector<std::array<protocol::Ressource, 7>>(size.back()));
    }});

    /**
    * @brief BCT -> [x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame]
    */
    protocol::_callbacks.insert({"bct", [](const std::string &data) -> void
    {
        const auto params = protocol::parse<u32>(data, 9);

        if (params.size() < 9) {
            throw zap::exception::Error("BCT", "Invalid number of parameters in bct command: ", params.size(), " expected 7");
        }

        const u32 x = params[0];
        const u32 y = params[1];
        std::array<protocol::Ressource, 7> ressources = {};

        for (u8 i = 0; i < 7; ++i) {
            ressources[i].type = static_cast<protocol::RessourceType>(i);
            ressources[i].quantity = params[i + 2];
        }

        if (x < _map.size() && y < _map[x].size()) {
            _map[x][y] = ressources;
        } else {
            throw zap::exception::Error("BCT", "Coordinates out of bounds in bct command");
        }
    }});

    /**
    * @brief set callback for receiving commands from the server
    */
    net->setCallback([](const std::string &line) -> void
    {
        const std::string cmd = line.substr(0, line.find(' '));

        if (protocol::_callbacks.contains(cmd)) {
            zap::logger::recv(cmd);
            const std::string line_without_cmd = std::string(line).substr(cmd.size());

            if (protocol::_callbacks.find(cmd) == protocol::_callbacks.end()) {
                throw zap::exception::Error("Protocol", "No callback registered for command: ", cmd);
            }

            protocol::_callbacks[cmd](line_without_cmd);
        }
    });
    // clang-format on

    stop();
    _network_thread = std::thread([net]() { net->start(); });
}
