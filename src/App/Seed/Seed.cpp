/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Seed.cpp
*/

#include <App/Seed/Create.hpp>

void zappy::create::seed(std::shared_ptr<zap::render::Scene> &scene, const std::vector<std::string> &obj_paths, const f32 radius, const u32 count, const Vector3 &scale)
{
    constexpr Vector3 center = {0, 0, 0};

    for (u32 i = 0; i < count; ++i) {
        Vector3 pos;

        for (u32 attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
            const f32 theta = static_cast<f32>(M_PI * (std::rand() / static_cast<f64>(RAND_MAX)));    //<< 0 to π
            const f32 phi = static_cast<f32>(2.0 * M_PI * (std::rand() / static_cast<f64>(RAND_MAX)));//<< 0 to 2π

            pos = {radius * sinf(theta) * cosf(phi), radius * cosf(theta), radius * sinf(theta) * sinf(phi)};
            pos = Vector3Add(center, pos);

            if (!is_too_close(pos, MIN_DISTANCE)) {
                break;
            }
        }

        __positions.push_back(pos);

        const auto obj = model(obj_paths[(maths::random<u32>(0, static_cast<u32>(obj_paths.size() - 1)))], pos);

        f32 angle;
        const Vector3 rotation = maths::rotation(pos, &angle);

        obj->setRotationAxis(rotation, angle);
        obj->setScale(scale);

        scene->add(std::move(obj));
    }
}
