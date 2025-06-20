/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Drawable.hpp
*/

#pragma once

#include <ZapGUI/Types.hpp>

namespace zap::abstract {

class Drawable
{
    public:
        virtual ~Drawable() = default;

        virtual void draw() const = 0;
        virtual void draw2D() const {};

        virtual bool has2D() const
        {
            return false;
        };

        virtual void update(const f32 dt) = 0;
};

}// namespace zap::abstract
