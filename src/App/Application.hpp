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
        Application(Client *client);
        ~Application() override = default;

        void init() override;

    private:
        Client *_client;
};

}// namespace zappy
