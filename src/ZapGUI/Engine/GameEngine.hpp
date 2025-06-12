/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** GameEngine.hpp
*/

#pragma once

#include <ZapGUI/Engine/RenderEngine.hpp>
#include <ZapGUI/Render/Scene.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace zap::abstract {

class GameEngine : public abstract::RenderEngine
{
    public:
        virtual ~GameEngine() = default;

        void startup() override;
        void render() override;
        void update() override;
        void shutdown() override;

    protected:
        void addScene(const std::string &name, std::shared_ptr<render::Scene> scene);
        void addToScene(const std::string &name, std::shared_ptr<abstract::Drawable> object);
        void addCamera(const std::string &name, std::shared_ptr<ZapCamera> camera);

    private:
        std::unordered_map<std::string, std::shared_ptr<render::Scene>> _scenes;
};

}// namespace zap::abstract
