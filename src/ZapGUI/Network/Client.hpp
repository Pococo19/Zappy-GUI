/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Client.hpp
*/

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

namespace zap {

class Client
{
    public:
        explicit Client(int port, const std::string &ip);
        ~Client() = default;

        void close();
        void connect();
        void send(const std::string& message);
        std::string receive(size_t bufferSize = 1024);

    private:
        int _port;
        std::string _ip;
        int _sock;
        sockaddr_in _serverAddr;
};

}
