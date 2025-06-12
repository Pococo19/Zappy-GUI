/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Drawable.hpp
*/

#pragma once

namespace zap::abstract {

class Drawable
{
    public:
        virtual ~Drawable() = default;
        virtual void draw() const = 0;
        virtual void update() = 0;
};

}// namespace zap::abstract
