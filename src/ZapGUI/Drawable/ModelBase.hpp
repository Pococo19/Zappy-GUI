/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ModelBase.hpp
*/

#pragma once

#include <ZapGUI/Raylib.hpp>

#include <string>
#include <vector>

namespace zap::abstract {

struct MaterialInfo {
        std::string name;
        std::string diffuse_map; //<< map_Kd
        std::string normal_map;  //<< map_Bump
        std::string alpha_map;   //<< map_d
        std::string specular_map;//<< map_Ks
};

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

    private:
        void _bind_textures(const std::vector<MaterialInfo> &materials);
};
}// namespace zap::abstract
