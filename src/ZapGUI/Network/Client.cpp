/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Client.cpp
*/

#include <ZapGUI/Error.hpp>
#include <ZapGUI/Logger.hpp>
#include <ZapGUI/Network/Client.hpp>

#include <vector>

zap::Client::Client(const u16 port, const std::string &ip) : _port(port), _ip(ip), _sock(-1)
{
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0) {
        throw exception::Error("Client::IP", "socket creation failed");
    }
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(static_cast<uint16_t>(_port));

    if (inet_pton(AF_INET, _ip.c_str(), &_server_addr.sin_addr) <= 0) {
        throw exception::Error("Client::IP", "Invalid IP address");
    }
}

void zap::Client::connect()
{
    if (::connect(_sock, reinterpret_cast<sockaddr *>(&_server_addr), sizeof(_server_addr)) < 0) {
        throw exception::Error("Client::connect", "server connection failed");
    }
    logger::debug("Client::connect", "Connected to server at: ", _ip, ":", _port);
}

void zap::Client::send(const std::string &message)
{
    const ssize_t sent = write(_sock, message.c_str(), message.size());

    if (sent < 0) {
        throw exception::Error("Client::send", "server sending failed");
    }
}

std::string zap::Client::receive(size_t bufferSize)
{
    std::vector<char> buffer(bufferSize, 0);
    const ssize_t br = read(_sock, buffer.data(), bufferSize - 1);

    if (br <= 0) {
        throw exception::Error("Client::receive", "server reception failed");
    }
    return buffer.data() + std::to_string(br);
}

void zap::Client::close()
{
    if (_sock >= 0) {
        ::close(_sock);
        _sock = -1;
    }
}
