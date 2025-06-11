/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** RenderLoop.hpp
*/

#pragma once

#include <ZapGUI/Engine/RenderEngine.hpp>
#include <ZapGUI/NonCopyable.hpp>
#include <ZapGUI/Network/Client.hpp>

#include <memory>

namespace zap::render {

class Loop final : public abstract::NonCopyable
{
    public:
        explicit Loop(abstract::RenderEngine *engine) noexcept;
        ~Loop() noexcept = default;
        void run() const noexcept;

    private:
        void _render() const noexcept;

        abstract::RenderEngine *_engine;
};

}// namespace zap::render
