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

        void add(std::shared_ptr<abstract::Drawable> object);
        void add(std::shared_ptr<ZapCamera> camera);
        void remove(abstract::Drawable *object);

        void render();
        void update(const f32 dt);

    private:
        std::vector<std::shared_ptr<zap::abstract::Drawable>> _objects;
        std::shared_ptr<ZapCamera> _camera;
};

}// namespace zap::render
