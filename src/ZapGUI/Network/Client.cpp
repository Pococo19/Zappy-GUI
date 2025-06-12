/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Client.cpp
*/

#include "ZapGUI/Network/Client.hpp"
#include <ZapGUI/Error.hpp>

zap::Client::Client(int port, const std::string &ip)
    : _port(port), _ip(ip), _sock(-1)
{
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0) {
        throw exception::Error("Client::IP", "socket creation failed");
    }
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(static_cast<uint16_t>(_port));

    if (inet_pton(AF_INET, _ip.c_str(), &_serverAddr.sin_addr) <= 0) {
        throw exception::Error("Client::IP", "Invalid IP address");
    }
}

void zap::Client::connect()
{
    if (::connect(_sock, reinterpret_cast<sockaddr*>(&_serverAddr), sizeof(_serverAddr)) < 0) {
        throw exception::Error("Client::connect", "server connection failed");
    }
    std::cout << "Connected to server." << std::endl;
}

void zap::Client::send(const std::string& message)
{
    ssize_t sent = write(_sock, message.c_str(), message.size());
    if (sent < 0) {
        throw exception::Error("Client::send", "server sending failed");
    }
}

std::string zap::Client::receive(size_t bufferSize)
{
    std::vector<char> buffer(bufferSize, 0);
    ssize_t bytesRead = read(_sock, buffer.data(), bufferSize - 1);

    if (bytesRead <= 0) {
        throw exception::Error("Client::receive", "server reception failed");
    }
    return buffer.data() + std::to_string(bytesRead);
}

void zap::Client::close()
{
    if (_sock >= 0) {
        ::close(_sock);
        _sock = -1;
    }
}
