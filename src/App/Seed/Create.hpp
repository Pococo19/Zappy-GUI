/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Create.hpp
*/

#pragma once

#if !defined(MIN_DISTANCE)
    #define MIN_DISTANCE 2.0f
#endif
#if !defined(MAX_ATTEMPTS)
    #define MAX_ATTEMPTS 100
#endif
#if !defined(COUNT_RANDOM_RANGE)
    #define COUNT_RANDOM_RANGE (2.5f, 3.0f)
#endif

#define ZAP_USE_RAYLIB_MATH
#include <App/Maths/Maths.hpp>
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

void seed(std::shared_ptr<zap::render::Scene> &scene, const std::vector<std::string> &obj_paths, const f32 radius, const u32 count, const Vector3 &scale);

[[nodiscard]] static inline u32 get_count(const f32 radius)
{
    const f32 spacing_offset = maths::random<f32> COUNT_RANDOM_RANGE;

    /** @brief A = 4πr² */
    const f32 surface = 4.f * PI * radius * radius;
    const f32 count = spacing_offset * spacing_offset;

    return static_cast<u32>(surface / count);
}

[[nodiscard]] static inline constexpr Vector3 get_scale(const f32 radius, const u32 width, const u32 height)
{
    const f32 scale_factor = std::max(static_cast<f32>(width), static_cast<f32>(height)) / (2.0f * radius) / 10;

    return {scale_factor, scale_factor, scale_factor};
}

void rocks(const protocol::GUI_Map &map, std::shared_ptr<zap::render::Scene> &out_scene, const f32 radius);
void trees(std::shared_ptr<zap::render::Scene> &out_scene, const Vector2u &map_size, const f32 radius);
void player(std::shared_ptr<zap::render::Scene> &scene, const f32 radius, const u32 width, const u32 height);
void system(std::shared_ptr<zap::render::Scene> &out_scene, std::shared_ptr<zap::ZapCamera> &camera, std::shared_ptr<BasePlanet> zappy);

}// namespace zappy::create
