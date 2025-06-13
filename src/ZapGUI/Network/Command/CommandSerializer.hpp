/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** CommandSerializer.hpp
*/

#pragma once

#include <ZapGUI/Network/Command/ICommand.hpp>

namespace zap::network {

class CommandSerializer
{
    public:
        static std::string serialize(const ICommand &cmd);
};

}// namespace zap::network
