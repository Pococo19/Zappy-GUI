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

#include <cmath>
#include <random>

static std::unique_ptr<zap::ZapModel> _create_model(const std::string &obj_path, const Vector3 &position)
{
    auto model = std::make_unique<zap::ZapModel>(obj_path, "assets/textures/");

    model->setPosition(position);
    return model;
}

static std::unique_ptr<zap::abstract::Drawable> _create_planet(const zappy::Planet &planet)
{
    const Mesh sphere = GenMeshSphere(planet._radius, 32, 32);
    const Model model = LoadModelFromMesh(sphere);
    auto p_model = std::make_unique<zap::ZapModel>(model);

    p_model->setPosition(planet._position);
    p_model->setTint(LIME);
    return p_model;
}

static i32 _get_random_between(const i32 min, const i32 max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<i32> dis(min, max);

    return dis(gen);
}

static void _add_models_around_planet(std::unique_ptr<zap::render::Scene> &scene, const std::vector<std::string> &obj_paths, const zappy::Planet &planet, u32 count)
{
    for (u32 i = 0; i < count; ++i) {
        const f32 theta = static_cast<f32>(M_PI * (std::rand() / static_cast<f64>(RAND_MAX)));    //<< 0 to π
        const f32 phi = static_cast<f32>(2.0 * M_PI * (std::rand() / static_cast<f64>(RAND_MAX)));//<< 0 to 2π
        const f32 radius = planet._radius;
        const Vector3 center = planet._position;

        Vector3 pos = {radius * sinf(theta) * cosf(phi), radius * cosf(theta), radius * sinf(theta) * sinf(phi)};

        pos = Vector3Add(center, pos);

        auto obj = _create_model(obj_paths[static_cast<u32>(_get_random_between(0, static_cast<i32>(obj_paths.size() - 1)))], pos);

        const Vector3 normal = Vector3Normalize(Vector3Subtract(pos, center));
        constexpr Vector3 up = {0, 1, 0};
        const Vector3 axis = Vector3CrossProduct(up, normal);
        const f32 angle = acosf(Vector3DotProduct(up, normal));

        if (Vector3Length(axis) > EPSILON) {
            obj->setRotationAxis(axis, angle * RAD2DEG);
        }

        scene->add(std::move(obj));
    }
}

// clang-format off
static const std::vector<std::string> _tree_models = {
    "assets/models/CommonTree_1.obj",
    "assets/models/CommonTree_2.obj",
    "assets/models/CommonTree_3.obj",
    "assets/models/CommonTree_4.obj"
};

static const std::vector<std::string> _flower_models = {
    "assets/models/Flower_3_Group.obj",
    "assets/models/Flower_4_Group.obj",
    "assets/models/Mushroom_Common.obj",
    "assets/models/Mushroom_Laetiporus.obj",
    "assets/models/Grass_Common_Tall.obj",
    "assets/models/Grass_Common_Short.obj",
    "assets/models/Grass_Wispy_Tall.obj",
    "assets/models/Grass_Wispy_Short.obj"
};

std::unique_ptr<zap::render::Scene> zappy::_create_main_scene()
{
    auto scene = std::make_unique<zap::render::Scene>();
    constexpr zappy::Planet planet = {{25, 0, 25}, 15.0f};

    scene->add(_create_planet(planet));
    _add_models_around_planet(scene, _tree_models, planet, 10);
    _add_models_around_planet(scene, _flower_models, planet, 50);
    scene->add(std::make_unique<zap::ZapCamera>());
    return scene;
}
