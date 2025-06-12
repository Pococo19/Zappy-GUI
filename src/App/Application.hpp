/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Application.hpp
*/

#include <ZapGUI/Engine/GameEngine.hpp>
#include <ZapGUI/Network/Client.hpp>

namespace zappy {

class Application final : public zap::abstract::GameEngine
{
    public:
        Application(zap::Client *client);
        ~Application() override = default;

        void init() override;
        void update() override;

    private:
        zap::Client *_client;
        std::string _serverResponse;
};

}// namespace zappy
