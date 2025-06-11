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
        Client(int port, const std::string &ip);
        ~Client();

        void closeSock();
        bool connectToServer();
        bool sendMessage(const std::string& message);
        std::string receiveMessage(size_t bufferSize = 1024);

    private:
        int _port;
        std::string _ip;
        int _sock;
        sockaddr_in _serverAddr;
};

}
