/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ICommand.hpp
*/

#pragma once

#include <string>

namespace zap::protocol {

struct ICommand {
        virtual ~ICommand() = default;
        virtual std::string name() const = 0;
};

}// namespace zap::protocol
