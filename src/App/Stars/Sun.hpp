/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Sun.hpp
*/

#pragma once

#include <App/Stars/BasePlanet.hpp>
#include <ZapGUI/Types.hpp>

#if !defined(ZAP_SHADER_SUN_ALREADY_DEFINED)
    #define ZAP_SHADER_SUN_VERT "assets/shaders/sun.vert"
    #define ZAP_SHADER_SUN_FRAG "assets/shaders/sun.frag"
    #define ZAP_SHADER_SUN_ALREADY_DEFINED
#endif

namespace zappy {

class Sun final : public zap::ShaderModel
{
    public:
        explicit Sun(const std::shared_ptr<zap::ZapCamera> &camera, const f32 zappy_radius);

        void draw() const override;
        void update(const f32 dt) override;

        void addPlanet(const std::shared_ptr<zappy::BasePlanet> &planet);

    private:
        void _init();

        f32 _rotation = 0.0f;
        i32 _timeLoc = 0;
        i32 _viewPosLoc = 0;
        i32 _mvpLoc = 0;
        i32 _matModelLoc = 0;

        f32 _zappy_radius = 0.0f;

        Model _stars;
        std::vector<Vector3> _stars_positions;
        std::vector<std::shared_ptr<zappy::BasePlanet>> _planets;
};

}// namespace zappy
