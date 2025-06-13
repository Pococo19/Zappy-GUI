/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** GameEngine.cpp
*/

#include <ZapGUI/Engine/GameEngine.hpp>
#include <ZapGUI/Event/EventCallback.hpp>
#include <ZapGUI/Logger.hpp>

/**
* public
*/

void zap::abstract::GameEngine::startup()
{
    logger::task_start("initializing game engine...");
    this->init();
    logger::task_done("game engine initialized");
}

void zap::abstract::GameEngine::render()
{
    for (const auto &scene : _scenes) {
        scene.second->render();
    }
}

void zap::abstract::GameEngine::update()
{
    for (const auto &scene : _scenes) {
        scene.second->update();
    }
    event::EventCallback::getInstance().listen();
}

/**
* protected
*/

void zap::abstract::GameEngine::addScene(const std::string &name, std::shared_ptr<render::Scene> scene)
{
    if (_scenes.contains(name)) {
        logger::debug("scene ", name, " already exists");
        return;
    }
    _scenes.emplace(name, std::move(scene));
}

void zap::abstract::GameEngine::addToScene(const std::string &name, std::shared_ptr<abstract::Drawable> object)
{
    if (!_scenes.contains(name)) {
        logger::debug("scene ", name, "does not exist, creating it");
        this->addScene(name, std::make_shared<render::Scene>());
    }
    _scenes.at(name)->add(std::move(object));
}

void zap::abstract::GameEngine::addCamera(const std::string &name, std::shared_ptr<ZapCamera> camera)
{
    if (!_scenes.contains(name)) {
        logger::debug("scene ", name, "does not exist, creating it");
        this->addScene(name, std::make_shared<render::Scene>());
    }
    _scenes.at(name)->add(std::move(camera));
}

void zap::abstract::GameEngine::shutdown()
{
    logger::task_start("shutting down game engine...");
    _scenes.clear();
    logger::task_done("game engine shut down");
}
