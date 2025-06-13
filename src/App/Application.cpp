/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Application.cpp
*/

#include <App/Application.hpp>
#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Event/EventCallback.hpp>
#include <ZapGUI/Logger.hpp>

#include <thread>

/**
* public
*/

zappy::Application::Application(const parser::Flags &flags)
{
    _net = std::make_unique<zap::NetworkClient>(flags.port, flags.hostname);
    _net->set_line_callback([&](const std::string &line) { zap::logger::debug(line); });
    _net_thread = std::thread([&]() {
        try {
            _net->send("GRAPHIC\n");
            _net->start();
        } catch (const zap::exception::Error &e) {
            zap::logger::error(e);
        }
    });
    zap::event::EventCallback::getInstance().add(KEY_ESCAPE, [&]() { _net->stop(); });
}

zappy::Application::~Application()
{
    if (_net) {
        _net->stop();
    }
    if (_net_thread.joinable()) {
        _net_thread.join();
    }
    zap::logger::debug("Application destroyed");
}

void zappy::Application::init()
{
    addScene("main", _create_main_scene());
}

void zappy::Application::update()
{
    zap::abstract::GameEngine::update();
}
