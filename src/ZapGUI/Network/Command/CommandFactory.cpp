/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** CommandFactory.cpp
*/

#include <ZapGUI/Error.hpp>
#include <ZapGUI/Network/Command/CommandFactory.hpp>

/**
* public
*/

void zap::network::CommandFactory::add(const std::string &pattern, ParserFn parser)
{
    if (_parsers.find(pattern) != _parsers.end()) {
        throw zap::exception::Error("CommandFactory", "Pattern already exists: ", pattern);
    }
    _parsers.insert({pattern, parser});
}

std::unique_ptr<zap::network::ICommand> zap::network::CommandFactory::parse(const std::string &line) const
{
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string word;

    while (iss >> word) {
        tokens.push_back(word);
    }

    if (tokens.empty()) {
        throw zap::exception::Error("CommandFactory", "Empty line");
    }

    const auto it = _parsers.find(tokens[0]);
    if (it == _parsers.end()) {
        throw zap::exception::Error("CommandFactory", "Unknown command: ", tokens[0]);
    }

    return it->second(tokens);
}
