/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Zappy.hpp
*/

#pragma once

#include <App/Protocol/Protocol.hpp>
#include <App/Stars/BasePlanet.hpp>

namespace zappy {

class Zappy final : public BasePlanet
{
    public:
        explicit Zappy(const protocol::GUI_Map &map, std::shared_ptr<zap::ZapCamera> camera);

        void setCamera(std::shared_ptr<zap::ZapCamera> camera);

    private:
        void _init(const protocol::GUI_Map &map);
};

}// namespace zappy
