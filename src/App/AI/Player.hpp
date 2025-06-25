/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Player.hpp
*/

#pragma once

#include <ZapGUI/Drawable/ModelAnim.hpp>

namespace zappy::ai {

class Player final : public zap::ZapModelAnim
{
    public:
        explicit Player(const std::string &id);

    private:
        std::string _id;
};

}// namespace zappy::ai
