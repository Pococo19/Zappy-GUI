/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Main.cpp
*/

#include <App/Application.hpp>
#include <ZapGUI/Context.hpp>

int main(void)
{
    return zap::context::run(std::make_unique<zappy::Application>(), {1920, 1080}, "Zappy", 120);
}
