/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Client.cpp
*/

#include <ZapGUI/Logger.hpp>
#include <ZapGUI/Network/Network.hpp>
#include <ZapGUI/Network/NetworkClient.hpp>

/**
* public
*/

zap::NetworkClient::NetworkClient(const u16 port, const std::string &ip) : _socket(-1), _buffer(), _line_cb(nullptr)
{
    _socket = network::socket();
    network::connect(_socket, port, ip);
}

void zap::NetworkClient::set_line_callback(std::function<void(std::string)> cb)
{
    _line_cb = std::move(cb);
}

void zap::NetworkClient::start()
{
    while (true) {
        const struct timeval timeout = {0, ZAP_NETWORK_CLIENT_TIMEOUT};

        if (network::select(_socket, timeout)) {
            do_read();
        }
    }
}
