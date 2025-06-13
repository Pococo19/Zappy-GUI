/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Client.cpp
*/

#include <ZapGUI/Network/Network.hpp>
#include <ZapGUI/Network/NetworkClient.hpp>

/**
* public
*/

zap::NetworkClient::NetworkClient(const u16 port, const std::string &ip) : _socket(-1), _buffer(), _callback(nullptr)
{
    _socket = network::socket();
    network::connect(_socket, port, ip);
}

zap::NetworkClient::~NetworkClient()
{
    if (_socket >= 0) {
        network::close(&_socket);
    }
}

void zap::NetworkClient::setCallback(Callback cb)
{
    _callback = std::move(cb);
}

void zap::NetworkClient::start()
{
    _running = true;

    while (_running) {
        const struct timeval timeout = {0, ZAP_NETWORK_CLIENT_TIMEOUT};

        if (network::select(_socket, timeout)) {
            this->receive();
        }
    }
}

void zap::NetworkClient::stop()
{
    _running = false;
}

void zap::NetworkClient::send(const std::string &message)
{
    if (message.empty()) {
        return;
    }

    const ssize_t written = network::write(_socket, message);

    if (written < 0) {
        throw exception::Error("NetworkClient::send", "Failed to send data: ", message, " with error code: ", std::to_string(errno));
    }
}

/**
* private
*/

void zap::NetworkClient::receive()
{
    char buffer[ZAP_NETWORK_CLIENT_BUFFER_SIZE];

    if (network::read(_socket, buffer) < 0) {
        return;
    }

    size_t pos;

    _buffer += buffer;

    while ((pos = _buffer.find('\n')) != std::string::npos) {
        const std::string line = _buffer.substr(0, pos);

        _buffer.erase(0, pos + 1);

        if (_callback) {
            _callback(line);
        }
    }
}
