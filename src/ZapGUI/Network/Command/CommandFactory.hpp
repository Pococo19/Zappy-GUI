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

namespace zap::network {

class CommandFactory
{
    public:
        using ParserFn = std::function<std::unique_ptr<ICommand>(const std::vector<std::string> &)>;

        void add(const std::string &pattern, ParserFn parser);

        std::unique_ptr<ICommand> parse(const std::string &command) const;

    private:
        std::unordered_map<std::string, ParserFn> _parsers;
};

}// namespace zap::network
