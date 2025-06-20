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

void zap::ZapCamera::update(const i32 mode) noexcept
{
    /** @brief camera direction */
    Vector3 forward = Vector3Subtract(_camera.target, _camera.position);

    /** @brief rotation around the "forward" axis (roll) */
    forward = Vector3Normalize(forward);

    bool manual_roll = false;

    if (IsKeyDown(KEY_Q)) {
        const Matrix rot = MatrixRotate(forward, -ROTATION_SPEED);
        _camera.up = Vector3Transform(_camera.up, rot);
        manual_roll = true;
    }
    if (IsKeyDown(KEY_E)) {
        const Matrix rot = MatrixRotate(forward, ROTATION_SPEED);
        _camera.up = Vector3Transform(_camera.up, rot);
        manual_roll = true;
    }

    if (manual_roll) {
        _camera.target = Vector3Add(_camera.position, forward);
        return;
    }
    UpdateCamera(&_camera, mode);
}

bool zap::ZapCamera::sees(const Vector3 &position) const noexcept
{
    const Vector3 to_target = Vector3Subtract(position, _camera.position);
    const Vector3 forward = _camera.target;
    const f32 dot = Vector3DotProduct(to_target, forward);

    return dot > 0.98f;
}

/**
* getters
*/

const Camera &zap::ZapCamera::get() const noexcept
{
    return _camera;
}

const Matrix zap::ZapCamera::getView() const noexcept
{
    return MatrixLookAt(_camera.position, _camera.target, _camera.up);
}

const Matrix zap::ZapCamera::getProjection() const noexcept
{
    if (_camera.projection == CAMERA_PERSPECTIVE) {
        const f64 aspect = static_cast<f64>(GetScreenWidth()) / GetScreenHeight();

        return MatrixPerspective(static_cast<f64>(DEG2RAD * _camera.fovy), aspect, 0.1, 100.0);
    }
    const f64 width = 10.0;
    const f64 height = 10.0;

    return MatrixOrtho(-width, width, -height, height, 0.1, 100.0);
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
