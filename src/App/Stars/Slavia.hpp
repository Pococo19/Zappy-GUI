/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Slavia.hpp
*/

#pragma once

#include <App/Protocol/Protocol.hpp>
#include <App/Stars/BasePlanet.hpp>

namespace zappy {

class Slavia final : public BasePlanet
{
    public:
        explicit Slavia(std::shared_ptr<zap::ZapCamera> camera, const f32 zappy_radius);

        void update(const f32 dt) override;

    private:
        void _init(const f32 zappy_radius);

        f32 _elapsed = 0.f;
        f32 _rotation = 0.f;
        f32 _zappy_radius = 0.f;
};

}// namespace zappy
