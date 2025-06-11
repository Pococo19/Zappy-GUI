/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Scene.cpp
*/

#include <ZapGUI/Error.hpp>
#include <ZapGUI/Render/Scene.hpp>

#include <algorithm>

/**
* public
*/

void zap::render::Scene::add(std::unique_ptr<zap::abstract::Drawable> object)
{
    _objects.emplace_back(std::move(object));
}

void zap::render::Scene::add(std::unique_ptr<ZapCamera> camera)
{
    _camera.reset();
    _camera = std::move(camera);
}

// clang-format off
void zap::render::Scene::remove(zap::abstract::Drawable *object)
{
    const auto it = std::remove_if(_objects.begin(), _objects.end(),
        [object]( const std::unique_ptr<zap::abstract::Drawable> &ptr)
        {
            return ptr.get() == object;
        });

    _objects.erase(it, _objects.end());
}
// clang-format on

void zap::render::Scene::render()
{
    if (!_camera) {
        throw exception::Error("Scene::render", "No camera set for the scene");
    }

    _camera->update();

    BeginMode3D(_camera->get());
    for (const auto &object : _objects) {
        object->draw();
    }
    EndMode3D();
}
