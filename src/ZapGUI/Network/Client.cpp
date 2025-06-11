/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Client.cpp
*/

#include "ZapGUI/Network/Client.hpp"
#include "Client.hpp"

zappy::Client::Client(const std::string& ip, int port)
    : _ip(ip),
    _port(port),
    _sock(-1)
{
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0) {
        std::cerr << "Erreur lors de la création du socket." << std::endl;
        return;
    }

    _serverAddr = {};
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(static_cast<uint16_t>(_port));

    if (inet_pton(AF_INET, _ip.c_str(), &_serverAddr.sin_addr) <= 0) {
        std::cerr << "Adresse invalide." << std::endl;
    }
}

zappy::Client::~Client()
{
    if (_sock >= 0) {
        close(_sock);
    }
}

bool zappy::Client::connectToServer()
{
    if (connect(_sock, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) < 0) {
        std::cerr << "Échec de connexion au serveur." << std::endl;
        return false;
    }
    std::cout << "Connecté au serveur !" << std::endl;
    return true;
}

bool zappy::Client::sendMessage(const std::string& message)
{
    if (send(_sock, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "Erreur lors de l'envoi du message." << std::endl;
        return false;
    }
    return true;
}

std::string zappy::Client::receiveMessage(size_t bufferSize)
{
    char* buffer = new char[bufferSize];
    std::memset(buffer, 0, bufferSize);

    ssize_t bytesRead = recv(_sock, buffer, bufferSize - 1, 0);
    std::string message = (bytesRead > 0) ? std::string(buffer) : "";

    delete[] buffer;
    return message;
}

void zappy::Client::closeSock()
{
    close(_sock);
}
