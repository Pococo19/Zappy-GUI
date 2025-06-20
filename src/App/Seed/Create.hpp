/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Create.hpp
*/

#pragma once

#define ZAP_USE_RAYLIB_MATH
#include <App/Stars/BasePlanet.hpp>
#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Render/Scene.hpp>

#include <App/Protocol/Protocol.hpp>

namespace zappy::create {

static std::vector<Vector3> __positions;

static inline bool is_too_close(const Vector3 &new_pos, f32 min_distance)
{
    for (const auto &existing_pos : __positions) {
        if (Vector3Distance(new_pos, existing_pos) < min_distance) {
            return true;
        }
    }
    return false;
}

static inline std::shared_ptr<zap::ZapModel> model(const std::string &obj_path, const Vector3 &position)
{
    const auto model = std::make_shared<zap::ZapModel>(obj_path, zap::Filename::getPath("assets/textures/"));

    model->setPosition(position);
    return model;
}

void rocks(const protocol::GUI_Map &map, std::shared_ptr<zap::render::Scene> &out_scene, const f32 radius);
void trees(std::shared_ptr<zap::render::Scene> &out_scene, const Vector2u &map_size, const f32 radius);
void player(std::shared_ptr<zap::render::Scene> &scene, const f32 radius, const u32 width, const u32 height);
void system(std::shared_ptr<zap::render::Scene> &out_scene, std::shared_ptr<zap::ZapCamera> &camera, std::shared_ptr<BasePlanet> zappy);

}// namespace zappy::create
