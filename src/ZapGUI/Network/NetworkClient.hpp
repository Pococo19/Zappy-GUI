/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** NetworkClient.hpp
*/

#pragma once

#include <ZapGUI/Types.hpp>

#include <atomic>
#include <functional>
#include <string>

#define ZAP_NETWORK_CLIENT_BUFFER_SIZE 1024
#define ZAP_NETWORK_CLIENT_TIMEOUT 10000

namespace zap {

class NetworkClient final
{
    public:
        explicit NetworkClient(const u16 port, const std::string &ip);
        ~NetworkClient();

        using Callback = std::function<void(std::string)>;

        void start();
        void stop();
        void send(const std::string &data);
        void setCallback(Callback cb);

    private:
        void receive();

        i32 _socket;
        std::string _buffer;
        Callback _callback;
        std::atomic<bool> _running{true};
};

}// namespace zap
