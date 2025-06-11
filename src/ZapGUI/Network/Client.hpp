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

namespace zappy {

class Client
{
    public:
        Client(const std::string& ip, int port);
        ~Client();

        bool connectToServer();
        bool sendMessage(const std::string& message);
        std::string receiveMessage(size_t bufferSize = 1024);
        void closeSock();

    private:
        std::string _ip;
        int _port;
        int _sock;
        sockaddr_in _serverAddr;
};

}
