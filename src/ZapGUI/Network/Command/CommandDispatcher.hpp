/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** CommandDispatcher.hpp
*/

#pragma once

#include <ZapGUI/Network/Command/ICommand.hpp>

#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace zap::network {

class CommandDispatcher
{
    public:
        template<typename T>
        void on(std::function<void(const T &)> callback)
        {
            const auto type = std::type_index(typeid(T));

            _callbacks[type].emplace_back([handler = std::move(callback)](const ICommand &base) { handler(static_cast<const T &>(base)); });
        }

        void dispatch(const ICommand &cmd);

    private:
        using CallbackFn = std::function<void(const ICommand &)>;
        std::unordered_map<std::type_index, std::vector<CallbackFn>> _callbacks;
};

}// namespace zap::network
