/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** MapSize.hpp
*/

#pragma once

#include <ZapGUI/Network/Command/ICommand.hpp>
#include <ZapGUI/Types.hpp>

namespace zappy::protocol {

struct MapSizeCommand : zap::network::ICommand {
        i32 width;
        i32 height;

        constexpr ~MapSizeCommand() override = default;
        static constexpr const char *_name = "msz";

        std::string name() const override
        {
            return _name;
        }
};

}// namespace zappy::protocol
