/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Camera.hpp
*/

#pragma once

#include <ZapGUI/NonCopyable.hpp>
#include <ZapGUI/Raylib.hpp>

namespace zap {

class ZapCamera final : public abstract::NonCopyable
{
    public:
        explicit ZapCamera() noexcept;
        ~ZapCamera() noexcept = default;

        void update(int mode = CAMERA_FREE) const noexcept;

        [[nodiscard]] const Camera &get() const noexcept;

        void setPosition(const Vector3 &position) noexcept;
        void setTarget(const Vector3 &target) noexcept;
        void setFovy(float fovy) noexcept;
        void setUp(const Vector3 &up) noexcept;
        void setProjection(int projection) noexcept;

    private:
        Camera _camera;
};

}// namespace zap
