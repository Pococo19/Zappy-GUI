/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ShaderModel.hpp
*/

#pragma once

#include <ZapGUI/Drawable.hpp>
#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Render/Camera.hpp>

namespace zap {

class ShaderModel : public abstract::Drawable
{
    public:
        explicit ShaderModel(std::shared_ptr<ZapCamera>);
        ~ShaderModel() override;

        void draw() const override;
        void update() override;

    protected:
        void _init();

        std::shared_ptr<ZapModel> _model;
        std::shared_ptr<ZapCamera> _camera;
        Shader _shader;
};

}// namespace zap
