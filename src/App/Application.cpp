/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Application.cpp
*/

#include <ZapGUI/Drawable/Model.hpp>

#include <App/Application.hpp>

/**
* public
*/

zappy::Application::Application(Client *client)
    : _client(client)
{
    if (!_client->connectToServer())
        std::cerr << "Failed to connect.\n";
}

static std::unique_ptr<zap::abstract::Drawable> _create_model(const std::string &obj_path)
{
    return std::make_unique<zap::ZapModel>(obj_path, "assets/textures/");
}

void zappy::Application::init()
{
    addScene("main", std::make_unique<zap::render::Scene>());
    addToScene("main", _create_model("assets/models/CommonTree_1.obj"));
    addCamera("main", std::make_unique<zap::ZapCamera>());
}

void zappy::Application::update()
{
    zap::abstract::GameEngine::update();
    // _serverResponse = _client->receiveMessage();
    _client->sendMessage("HELLOOO");
}
