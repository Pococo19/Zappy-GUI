/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** BasePlanet.hpp
*/

#pragma once

#if !defined(ZAP_PLANET_SHADER_ALREADY_DEFINED)
    #define ZAP_SHADER_PLANET_VERT "assets/shaders/planet.vert"
    #define ZAP_SHADER_PLANET_FRAG "assets/shaders/planet.frag"
    #define ZAP_PLANET_SHADER_ALREADY_DEFINED
#endif

#include <ZapGUI/Drawable/ShaderModel.hpp>
#include <ZapGUI/Render/Camera.hpp>

namespace zappy {

class BasePlanet : public zap::ShaderModel
{
    public:
        explicit BasePlanet(std::shared_ptr<zap::ZapCamera>);

        void draw() const override;
        void update() override;

        f32 getRadius() const;
        Vector3 getPosition() const;

        void setColor(const Vector3 &color);

        void applyLighting(const Vector3 &light_pos, const Vector3 &light_color, const f32 light_intensity);

    protected:
        void _setup_shader();

        i32 _timeLoc = -1;
        i32 _viewPosLoc = -1;
        i32 _lightPosLoc = -1;
        i32 _lightColorLoc = -1;
        i32 _lightIntensityLoc = -1;
        i32 _planetBaseColorLoc = -1;

        f32 _radius = 0.0f;
        f32 _rotation = 0.0f;

        Vector3 _color = {1.0f, 1.0f, 1.0f};
};

}// namespace zappy
