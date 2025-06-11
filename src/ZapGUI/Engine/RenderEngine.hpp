/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** RenderEngine.hpp
*/

#pragma once

namespace zap::abstract {

class RenderEngine
{
    public:
        virtual ~RenderEngine() = default;

        virtual void init() = 0;
        virtual void startup() = 0;
        virtual void render() = 0;
        virtual void shutdown() = 0;
        virtual void update() = 0;
};

}// namespace zap::abstract
