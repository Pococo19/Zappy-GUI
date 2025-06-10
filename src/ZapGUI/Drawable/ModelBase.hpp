/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ModelBase.hpp
*/

#pragma once

#include <ZapGUI/Raylib.hpp>

#include <string>

namespace zap::abstract {

class ModelBase
{
    public:
        virtual ~ModelBase() = default;

        void setPosition(const Vector3 &position);
        Vector3 getPosition() const;

        void setScale(float scale);
        float getScale() const;

        void setTint(const Color &tint);
        Color getTint() const;

    protected:
        Model _model;
        Texture _texture;

        Vector3 _position = {0.0f, 0.0f, 0.0f};
        float _scale = 1.0f;
        Color _tint = WHITE;

        void _load_textures(const std::string &obj_file, const std::string &texture_directory);
};
}// namespace zap::abstract
