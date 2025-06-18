/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Atmosphere.hpp
*/

#pragma once

#include <ZapGUI/Drawable/ShaderModel.hpp>
#include <ZapGUI/Filename.hpp>

namespace zappy {

class Atmosphere final : public zap::ShaderModel
{
public:
    explicit Atmosphere(Shader &shader, std::shared_ptr<zap::ZapModel> model, std::shared_ptr<zap::ZapCamera> camera);
    void draw() const override;
};

} // namespace zappy