/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Player.cpp
*/

#include <App/AI/Player.hpp>
#include <ZapGUI/Drawable/ModelAnim.hpp>
#include <ZapGUI/Filename.hpp>

static const std::string _obj_path = zap::Filename::getPath("assets/models/Bot.glb");

/**
* public
*/

zappy::ai::Player::Player(const std::string &id) : ZapModelAnim(_obj_path), _id(id)
{
    /* __ctor__ */
}

void zappy::ai::Player::setAnimation(const Animation &animation)
{
    if (_animation == animation) {
        return;
    }
    _animation = animation;

    switch (animation) {
        case Animation::NONE:
            _anim_index = 0;
            break;
        case Animation::INCANTATION:
            _anim_index = 1;
            break;
        case Animation::EGG:
            break;
        case Animation::DEATH:
            _anim_index = 2;
            break;
        default:
            _anim_index = 0;
            break;
    }
}

/**
* private
*/
