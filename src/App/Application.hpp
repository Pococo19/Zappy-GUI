/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Application.hpp
*/

#include <ZapGUI/Engine/GameEngine.hpp>

namespace zappy {

class Application final : public zap::abstract::GameEngine
{
    public:
        explicit Application() = default;
        ~Application() override = default;

        void init() override;
        void update() override;

    private:
};

}// namespace zappy
