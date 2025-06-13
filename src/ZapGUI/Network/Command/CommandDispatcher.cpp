/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** CommandDispatcher.cpp
*/

#include <ZapGUI/Network/Command/CommandDispatcher.hpp>
#include <typeindex>

/**
* public
*/

void zap::network::CommandDispatcher::dispatch(const ICommand &cmd)
{
    const auto type = std::type_index(typeid(cmd.name()));
    const auto it = _callbacks.find(type);

    if (it != _callbacks.end()) {
        for (const auto &callback : it->second) {
            callback(cmd);
        }
    }
}
