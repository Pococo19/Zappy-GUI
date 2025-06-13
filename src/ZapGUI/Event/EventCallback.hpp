/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** EventCallback.hpp
*/

#pragma once

#include <ZapGUI/NonCopyable.hpp>
#include <ZapGUI/Types.hpp>

#include <functional>

namespace zap::event {

class EventCallback final : public abstract::NonCopyable
{
    public:
        using Callback = std::function<void()>;

        static EventCallback &getInstance();

        void add(i32 key, Callback callback);
        void listen() const;

    private:
        std::vector<std::pair<i32, Callback>> _callbacks;
};

}// namespace zap::event
