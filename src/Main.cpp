/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Main.cpp
*/

#include <App/Application.hpp>
#include <ZapGUI/Context.hpp>

int main(int ac, char **av)
{
    if (ac < 5) {
        std::cerr << "Usage: " << av[0] << " -p <port> -h <hostname>\n";
        return 84;
    }
    std::cout << "Connecting to server at " << av[2] << ":" << av[4] << "...\n";

    auto client = std::make_unique<zap::Client>(std::stoi(av[2]), av[4]);
    return zap::context::run(std::make_unique<zappy::Application>(client.get()), {1920, 1080}, "Zappy", 120);
}
