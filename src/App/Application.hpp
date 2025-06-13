/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Application.hpp
*/

#include <App/Arguments.hpp>
#include <App/Protocol/Protocol.hpp>

#include <ZapGUI/Engine/GameEngine.hpp>
#include <ZapGUI/Network/NetworkClient.hpp>

namespace zappy {

struct Planet {
        Vector3 _position;
        f32 _radius;
};

class Application final : public zap::abstract::GameEngine
{
    public:
        Application(const parser::Flags &flags);
        ~Application() override;

        void init() override;
        void update() override;

    private:
        std::shared_ptr<zap::NetworkClient> _net;

        void _init_network();
};

std::shared_ptr<zap::render::Scene> _create_main_scene();

}// namespace zappy
