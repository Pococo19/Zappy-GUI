/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Network.hpp
*/

#pragma once

#include <ZapGUI/Error.hpp>
#include <ZapGUI/Types.hpp>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

/**
* @brief Network utilities encapsulation of C functions
*/

namespace zap::network {

/**
* @brief create a socket and set it to non-blocking mode
*
* @throws exception::Error if the socket creation fails
* @throws exception::Error if setting the socket to non-blocking mode fails
*
* @return socket file descriptor
*/
[[nodiscard]] static inline i32 socket()
{
    const int opt = 1;
    i32 sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        throw exception::Error("NetworkClient", "Failed to create socket");
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        throw exception::Error("NetworkClient", "Failed to set socket options");
    }
    return sock;
}

/**
* @brief connect to a server using the given port and IP address
*
* @param socket the socket file descriptor
* @param port the port to connect to
* @param ip the IP address to connect to
*
* @throws exception::Error if the IP address is invalid
* @throws exception::Error if the connection fails
* @throws exception::Error if setting the socket to non-blocking mode fails
*
* @return void
*/
static inline void connect(const int socket, const u16 port, const std::string &ip)
{
    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) {
        throw exception::Error("NetworkClient", "Invalid IP address");
    }
    if (::connect(socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        throw exception::Error("NetworkClient", "Failed to connect to server");
    }
    if (fcntl(socket, F_SETFL, O_NONBLOCK) < 0) {
        throw exception::Error("NetworkClient", "Failed to set socket to non-blocking mode");
    }
}

/**
* @brief select function to wait for data on a socket
*
* @param socket the socket file descriptor to monitor
* @param timeout the timeout for the select call
*
* @throws exception::Error if the select call fails
*
* @return true if data is available on the socket, false otherwise
*/
[[nodiscard]] static inline bool select(i32 socket, timeval timeout)
{
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(socket, &readfds);

    const int rv = ::select(socket + 1, &readfds, nullptr, nullptr, &timeout);

    if (rv < 0) {
        throw exception::Error("NetworkClient", "Select failed");
    } else if (FD_ISSET(socket, &readfds)) {
        return true;
    }
    return false;
}

/**
* @brief read data from a socket into a buffer
*
* @param socket the socket file descriptor to read from
* @param buffer the buffer to read data into
*
* @returns the number of bytes read
*/
[[nodiscard]] static inline ssize_t read(i32 socket, char *buffer)
{
    const ssize_t br = ::read(socket, buffer, sizeof(buffer) - 1);

    if (br < 0) {
        return br;
    }

    buffer[br] = '\0';
    return br;
}

/**
* @brief write data to a socket from a string
*
* @param socket the socket file descriptor to write to
* @param data the string data to write
*
* @return the number of bytes written
*/
[[nodiscard]] static inline ssize_t write(i32 socket, const std::string &data)
{
    return ::write(socket, data.c_str(), data.size());
}

/**
* @brief close a socket and set its file descriptor to -1
*
* @param socket pointer to the socket file descriptor
*
* @return void
*/
static inline void close(i32 *socket)
{
    if (*socket < 0) {
        return;
    }
    ::close(*socket);
    *socket = -1;
}

}// namespace zap::network
