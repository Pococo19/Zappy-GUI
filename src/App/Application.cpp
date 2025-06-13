/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Application.cpp
*/

#include <App/Application.hpp>
#include <App/Protocol/Protocol.hpp>

#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Event/EventCallback.hpp>
#include <ZapGUI/Logger.hpp>

#include <thread>

/**
* public
*/

zappy::Application::Application(const parser::Flags &flags)
{
    _net = std::make_shared<zap::NetworkClient>(flags.port, flags.hostname);
    _init_network();
}

zappy::Application::~Application()
{
    if (_net) {
        _net->stop();
    }
    protocol::stop();
    zap::logger::debug("Application destroyed");
}

void zappy::Application::init()
{
    // addScene("main", _create_main_scene(protocol::_map));
}

void zappy::Application::update()
{
    zap::abstract::GameEngine::update();
}

/**
* private
*/

void zappy::Application::_init_network()
{
    zap::event::EventCallback::getInstance().add(KEY_ESCAPE, [&]() { _net->stop(); });
    protocol::init(_net);
}
