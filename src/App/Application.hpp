/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Application.hpp
*/

#include <ZapGUI/Engine/GameEngine.hpp>

namespace zappy {

struct Planet {
        Vector3 _position;
        f32 _radius;
};

class Application final : public zap::abstract::GameEngine
{
    public:
        explicit Application() = default;
        ~Application() override = default;

        void init() override;
        void update() override;

    private:
};

std::unique_ptr<zap::render::Scene> _create_main_scene();

}// namespace zappy
