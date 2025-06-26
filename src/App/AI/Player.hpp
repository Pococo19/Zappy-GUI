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
        ~Player() override = default;

        enum class Animation { NONE, INCANTATION, EGG, DEATH };

        void setAnimation(const Animation &animation);

    private:
        std::string _id;
        Animation _animation = Animation::NONE;
};

}// namespace zappy::ai
