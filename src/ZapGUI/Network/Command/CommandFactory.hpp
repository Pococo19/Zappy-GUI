/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** CommandFactory.hpp
*/

#pragma once

#include <ZapGUI/Network/Command/ICommand.hpp>

#include <functional>
#include <memory>
#include <regex>
#include <unordered_map>

namespace zap::protocol {

class CommandFactory
{
    public:
        std::unique_ptr<ICommand> parse(const std::string &command) const;

    private:
        using ParserFn = std::function<std::unique_ptr<ICommand>(const std::smatch &)>;
        std::unordered_map<std::string, ParserFn> _parsers;
};

}// namespace zap::protocol
