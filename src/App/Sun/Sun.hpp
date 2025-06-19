/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Sun.hpp
*/

#pragma once

#include <ZapGUI/Drawable/ShaderModel.hpp>
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
        explicit Sun(const std::shared_ptr<zap::ZapCamera> &camera);

        void draw() const override;
        void update() override;

    protected:
        void _init();

    private:
        f32 _rotation = 0.0f;
        i32 _timeLoc = 0;
        i32 _viewPosLoc = 0;
        i32 _mvpLoc = 0;
        i32 _matModelLoc = 0;
};

}// namespace zappy
