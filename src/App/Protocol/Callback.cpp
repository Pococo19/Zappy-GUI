/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Callback.cpp
*/

#include <App/Protocol/Callback.hpp>
#include <ZapGUI/Logger.hpp>

/**
* public
*/

zappy::protocol::Callback &zappy::protocol::Callback::getInstance()
{
    static Callback instance;

    return instance;
}

void zappy::protocol::Callback::add(const std::string &cmd, const std::function<void(const std::string &)> &callback)
{
    if (contains(cmd)) {
        zap::logger::debug("WARN! command ", cmd, " already exists, overwriting it");
    }
    _commands[cmd] = callback;
}

bool zappy::protocol::Callback::contains(const std::string &cmd) const
{
    return _commands.contains(cmd);
}

#pragma message("CHANGE BEFORE PUSH TO PRODUCTION: remove this message and the commented throw in call()")

void zappy::protocol::Callback::call(const std::string &cmd, const std::string &data) const
{
    if (!contains(cmd)) {
        return;
        // throw zap::exception::Error("Callback", "No callback registered for command: ", cmd);
    }
    _commands.at(cmd)(data);
}

void zappy::protocol::Callback::clear()
{
    _commands.clear();
}
