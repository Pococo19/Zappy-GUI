/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Application.cpp
*/

#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Logger.hpp>

#include <App/Application.hpp>

/**
* public
*/

static std::unique_ptr<zap::abstract::Drawable> _create_model(const std::string &obj_path)
{
    return std::make_unique<zap::ZapModel>(obj_path, "assets/textures/");
}

static std::unique_ptr<zap::abstract::Drawable> _create_heightmap(const std::string &obj_path)
{
    auto kurwa_mesh = zap::ZapModel::from_heightmap(obj_path);
    const auto mac_pos = kurwa_mesh->getPosition();

    kurwa_mesh->setPosition({mac_pos.x, mac_pos.y - 30, mac_pos.z});
    kurwa_mesh->setTint(LIME);
    return kurwa_mesh;
}

void zappy::Application::init()
{
    addScene("main", std::make_unique<zap::render::Scene>());
    addToScene("main", _create_heightmap("assets/textures/heightmap.png"));
    addToScene("main", _create_model("assets/models/CommonTree_1.obj"));
    addCamera("main", std::make_unique<zap::ZapCamera>());
}

void zappy::Application::update()
{
    zap::abstract::GameEngine::update();
}
