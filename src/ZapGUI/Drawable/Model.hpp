/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Model.hpp
*/

#pragma once

#include <ZapGUI/Drawable.hpp>
#include <ZapGUI/Drawable/ModelBase.hpp>

namespace zap {

class ZapModel final : public abstract::ModelBase, public abstract::Drawable
{
    public:
        explicit ZapModel(const std::string &obj_path, const std::string &texture_directory = "");
        ~ZapModel();

        void draw() const override;
};
}// namespace zap
