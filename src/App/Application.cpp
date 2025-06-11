/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Application.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>

#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Logger.hpp>

#include <App/Application.hpp>

#include <random>

/**
* public
*/

static std::unique_ptr<zap::ZapModel> _create_model(const std::string &obj_path, const Vector3 &position)
{
    auto model = std::make_unique<zap::ZapModel>(obj_path, "assets/textures/");

    model->setPosition(position);
    return model;
}

static std::unique_ptr<zap::abstract::Drawable> _create_planet(const zappy::Planet &planet)
{
    Mesh sphere = GenMeshSphere(planet._radius, 32, 32);
    Model model = LoadModelFromMesh(sphere);
    auto p_model = std::make_unique<zap::ZapModel>(model);

    p_model->setPosition(planet._position);
    p_model->setTint(LIME);
    return p_model;
}

static i32 _get_random_between(i32 min, i32 max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<i32> dis(min, max);

    return dis(gen);
}

static void _add_trees_around_planet(std::unique_ptr<zap::render::Scene> &scene, const Vector3 &planetCenter, f32 radius, int count)
{
    for (int i = 0; i < count; ++i) {
        const f32 theta = static_cast<f32>(M_PI * (std::rand() / static_cast<f64>(RAND_MAX)));    // 0 to π
        const f32 phi = static_cast<f32>(2.0 * M_PI * (std::rand() / static_cast<f64>(RAND_MAX)));// 0 to 2π

        Vector3 pos = {radius * std::sinf(theta) * std::cosf(phi), radius * std::cosf(theta), radius * std::sinf(theta) * std::sinf(phi)};

        pos = Vector3Add(planetCenter, pos);

        auto tree = _create_model("assets/models/CommonTree_" + std::to_string(_get_random_between(1, 4)) + ".obj", pos);

        const Vector3 normal = Vector3Normalize(Vector3Subtract(pos, planetCenter));
        constexpr Vector3 up = {0, 1, 0};
        const Vector3 axis = Vector3CrossProduct(up, normal);
        const f32 angle = acosf(Vector3DotProduct(up, normal));

        if (Vector3Length(axis) > EPSILON) {
            tree->setRotationAxis(axis, angle * RAD2DEG);
        }

        scene->add(std::move(tree));
    }
}

static std::unique_ptr<zap::render::Scene> _create_main_scene()
{
    auto scene = std::make_unique<zap::render::Scene>();
    zappy::Planet planet = {{25, 0, 25}, 15.0f};

    scene->add(_create_planet(planet));
    _add_trees_around_planet(scene, planet._position, planet._radius + 0.5f, 10);
    scene->add(std::make_unique<zap::ZapCamera>());
    return scene;
}

void zappy::Application::init()
{
    addScene("main", _create_main_scene());
}

void zappy::Application::update()
{
    zap::abstract::GameEngine::update();
}
