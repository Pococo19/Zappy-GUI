/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Client.hpp
*/

#pragma once

#include <ZapGUI/Types.hpp>

#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <unistd.h>

namespace zap {

class Client final
{
    public:
        explicit Client(const u16 port, const std::string &ip);
        ~Client() = default;

        void close();
        void connect();
        void send(const std::string &message);
        std::string receive(size_t bufferSize = 1024);

    private:
        u16 _port;
        std::string _ip;
        i32 _sock;
        sockaddr_in _server_addr;
};

}// namespace zap
