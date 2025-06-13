/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** NetworkClient.hpp
*/

#pragma once

#include <ZapGUI/Types.hpp>

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

        void start();
        void send(const std::string &data);
        void set_line_callback(std::function<void(std::string)> cb);

    private:
        void do_read();

        i32 _socket;
        std::string _buffer;
        std::function<void(std::string)> _line_cb;
};

}// namespace zap
