/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Model.hpp
*/

#pragma once

#include <ZapGUI/Drawable.hpp>
#include <ZapGUI/Drawable/ModelBase.hpp>

#include <memory>

namespace zap {

class ZapModel final : public abstract::ModelBase, public abstract::Drawable
{
    public:
        explicit ZapModel(const std::string &obj_path, const std::string &texture_directory = "");
        explicit ZapModel(const Model &model);

        ~ZapModel();

        static std::unique_ptr<ZapModel> from_heightmap(const std::string &obj_path);

        void draw() const override;
};
}// namespace zap
