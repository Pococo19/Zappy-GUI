/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Drawable.hpp
*/

namespace zap::abstract {

class Drawable
{
    public:
        virtual ~Drawable() = default;
        virtual void draw() const = 0;
};

}// namespace zap::abstract
