/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Main.cpp
*/

#include <App/Application.hpp>

#include <ZapGUI/Context.hpp>
#include <ZapGUI/Logger.hpp>
#include <ZapGUI/Macro.hpp>

int main(const int argc, const char **argv)
{
    try {
        const zappy::Flags flags = zappy::parse(argc, argv);

        zap::context::run(std::make_unique<zappy::Application>(flags), ZAP_DEFAULT_WINDOW_SIZE, "Zappy", ZAP_DEFAULT_MAX_FRAMERATE);

    } catch (const zap::exception::Error &e) {
        zap::logger::error(e);
        return ERROR;
    }

    return SUCCESS;
}
