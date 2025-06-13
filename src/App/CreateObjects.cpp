/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** CreateObjects.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>

#include <App/Application.hpp>
#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Logger.hpp>

#include <ZapGUI/Filename.hpp>

#include <cmath>
#include <random>

// static std::shared_ptr<zap::ZapModel> _create_model(const std::string &obj_path, const Vector3 &position)
// {
//     auto model = std::make_shared<zap::ZapModel>(obj_path, zap::Filename::getPath("assets/textures/"));
//
//     model->setPosition(position);
//     return model;
// }
//
static std::shared_ptr<zap::abstract::Drawable> _create_planet(const zappy::Planet &planet)
{
    const Mesh sphere = GenMeshSphere(planet._radius, 32, 32);
    const Model model = LoadModelFromMesh(sphere);
    auto p_model = std::make_shared<zap::ZapModel>(model);

    p_model->setPosition(planet._position);
    p_model->setTint(LIME);
    return p_model;
}
//
// static i32 _get_random_between(const i32 min, const i32 max)
// {
//     static std::random_device rd;
//     static std::mt19937 gen(rd());
//
//     std::uniform_int_distribution<i32> dis(min, max);
//
//     return dis(gen);
// }
//
static std::vector<Vector3> __positions;
//
// static inline bool _is_position_too_close(const Vector3 &new_pos, f32 min_distance)
// {
//     for (const auto &existing_pos : __positions) {
//         if (Vector3Distance(new_pos, existing_pos) < min_distance) {
//             return true;
//         }
//     }
//     return false;
// }

// static void _seed_models_around_planet(std::shared_ptr<zap::render::Scene> &scene, const std::vector<std::string> &obj_paths, const zappy::Planet &planet, u32 count)
// {
//     constexpr f32 MIN_DISTANCE = 2.0f;
//     constexpr u32 MAX_ATTEMPTS = 100;
//
//     for (u32 i = 0; i < count; ++i) {
//         Vector3 pos;
//         Vector3 center;
//         bool valid_position_found = false;
//
//         for (u32 attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
//             const f32 theta = static_cast<f32>(M_PI * (std::rand() / static_cast<f64>(RAND_MAX)));    //<< 0 to π
//             const f32 phi = static_cast<f32>(2.0 * M_PI * (std::rand() / static_cast<f64>(RAND_MAX)));//<< 0 to 2π
//             const f32 radius = planet._radius;
//             center = planet._position;
//
//             pos = {radius * sinf(theta) * cosf(phi), radius * cosf(theta), radius * sinf(theta) * sinf(phi)};
//             pos = Vector3Add(center, pos);
//
//             if (!_is_position_too_close(pos, MIN_DISTANCE)) {
//                 valid_position_found = true;
//                 break;
//             }
//         }
//
//         if (!valid_position_found) {
//             zap::logger::debug("Could not find a valid position for object", i, " after ", MAX_ATTEMPTS, " attempts");
//         }
//
//         __positions.push_back(pos);
//
//         auto obj = _create_model(obj_paths[static_cast<u32>(_get_random_between(0, static_cast<i32>(obj_paths.size() - 1)))], pos);
//
//         const Vector3 normal = Vector3Normalize(Vector3Subtract(pos, center));
//         constexpr Vector3 up = {0, 1, 0};
//         const Vector3 axis = Vector3CrossProduct(up, normal);
//         const f32 angle = acosf(Vector3DotProduct(up, normal));
//
//         if (Vector3Length(axis) > EPSILON) {
//             obj->setRotationAxis(axis, angle * RAD2DEG);
//         }
//
//         scene->add(std::move(obj));
//     }
// }

static inline void _clear_positions()
{
    __positions.clear();
}

// clang-format off
static const std::vector<std::string> _tree_models = {
    zap::Filename::getPath("assets/models/CommonTree_1.obj"),
    zap::Filename::getPath("assets/models/CommonTree_2.obj"),
    zap::Filename::getPath("assets/models/CommonTree_3.obj"),
    zap::Filename::getPath("assets/models/CommonTree_4.obj"),
};

static const std::vector<std::string> _flower_models = {
    zap::Filename::getPath("assets/models/Flower_3_Group.obj"),
    zap::Filename::getPath("assets/models/Flower_4_Group.obj"),
    zap::Filename::getPath("assets/models/Mushroom_Common.obj"),
    zap::Filename::getPath("assets/models/Mushroom_Laetiporus.obj"),
    zap::Filename::getPath("assets/models/Grass_Common_Tall.obj"),
    zap::Filename::getPath("assets/models/Grass_Common_Short.obj"),
    zap::Filename::getPath("assets/models/Grass_Wispy_Tall.obj"),
    zap::Filename::getPath("assets/models/Grass_Wispy_Short.obj")
};
// clang-format on

std::shared_ptr<zap::render::Scene> zappy::_create_main_scene()
{
    _clear_positions();

    auto scene = std::make_shared<zap::render::Scene>();
    constexpr zappy::Planet planet = {{25, 0, 25}, 15.0f};

    scene->add(_create_planet(planet));
    // _seed_models_around_planet(scene, _tree_models, planet, 10);
    // _seed_models_around_planet(scene, _flower_models, planet, 50);
    scene->add(std::make_shared<zap::ZapCamera>());
    return scene;
}
