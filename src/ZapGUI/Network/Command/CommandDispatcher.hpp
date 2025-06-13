/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** CommandDispatcher.hpp
*/

#pragma once

#include <ZapGUI/Network/Command/ICommand.hpp>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace zap::protocol {

class CommandDispatcher
{
    public:
        template<typename T>
        void on(std::function<void(const T &)> callback);
        void dispatch(const ICommand &cmd);

    private:
        using CallbackFn = std::function<void(const ICommand &)>;
        std::unordered_map<std::string, std::vector<CallbackFn>> _callbacks;
};

}// namespace zap::protocol
