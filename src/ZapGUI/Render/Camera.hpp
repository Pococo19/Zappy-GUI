/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Camera.hpp
*/

#pragma once

#include <ZapGUI/NonCopyable.hpp>
#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Raylib.hpp>
#include <ZapGUI/Types.hpp>

namespace zap {

class ZapCamera final : public abstract::NonCopyable
{
    public:
        explicit ZapCamera() noexcept;
        ~ZapCamera() noexcept = default;

        void update() noexcept;

        [[nodiscard]] const Camera &get() const noexcept;
        [[nodiscard]] bool sees(const Vector3 &position) const noexcept;

        void setPosition(const Vector3 &position) noexcept;
        void setTarget(const Vector3 &target) noexcept;
        void setFovy(f32 fovy) noexcept;
        void setUp(const Vector3 &up) noexcept;
        void setProjection(i32 projection) noexcept;

        [[nodiscard]] const Matrix getView() const noexcept;
        [[nodiscard]] const Matrix getProjection() const noexcept;

    private:
        Camera _camera;

        f32 _move_speed = 5.0f;
        f32 _rotation_speed = 2.0f;
        f32 _sensitivity = 0.003f;
};

}// namespace zap
