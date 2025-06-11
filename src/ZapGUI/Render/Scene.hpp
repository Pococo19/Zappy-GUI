/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Scene.hpp
*/

#pragma once

#include <memory>
#include <vector>

#include <ZapGUI/Drawable.hpp>
#include <ZapGUI/NonCopyable.hpp>
#include <ZapGUI/Render/Camera.hpp>

namespace zap::render {

class Scene final : abstract::NonCopyable
{
    public:
        constexpr explicit Scene() = default;
        ~Scene() = default;

        void add(std::unique_ptr<abstract::Drawable> object);
        void add(std::unique_ptr<ZapCamera> camera);
        void remove(abstract::Drawable *object);

        void render();

    private:
        std::vector<std::unique_ptr<zap::abstract::Drawable>> _objects;
        std::unique_ptr<ZapCamera> _camera;
};

}// namespace zap::render
