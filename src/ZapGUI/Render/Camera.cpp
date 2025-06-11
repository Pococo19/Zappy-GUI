/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Camera.cpp
*/

#include <ZapGUI/Render/Camera.hpp>

/**
* @brief Camera is a C struct, so we need to wrap it in a C++ class
*/

/**
* public
*/

zap::ZapCamera::ZapCamera() noexcept
{
    _camera.position = {4.0f, 4.0f, 4.0f};
    _camera.target = {0.0f, 0.0f, 0.0f};
    _camera.up = {0.0f, 1.0f, 0.0f};
    _camera.fovy = 70.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
}

void zap::ZapCamera::update(i32 mode) const noexcept
{
    Camera *ptr = const_cast<Camera *>(&_camera);

    UpdateCamera(ptr, mode);
}

/**
* getters
*/

const Camera &zap::ZapCamera::get() const noexcept
{
    return _camera;
}

/**
* setters
*/

void zap::ZapCamera::setPosition(const Vector3 &position) noexcept
{
    _camera.position = position;
}

void zap::ZapCamera::setTarget(const Vector3 &target) noexcept
{
    _camera.target = target;
}

void zap::ZapCamera::setFovy(f32 fovy) noexcept
{
    _camera.fovy = fovy;
}

void zap::ZapCamera::setUp(const Vector3 &up) noexcept
{
    _camera.up = up;
}

void zap::ZapCamera::setProjection(i32 projection) noexcept
{
    _camera.projection = projection;
}
