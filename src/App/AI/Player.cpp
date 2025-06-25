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

/**
* private
*/
