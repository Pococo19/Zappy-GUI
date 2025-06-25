/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Camera.cpp
*/

#include "ZapGUI/Event/EventCallback.hpp"
#include <ZapGUI/Render/Camera.hpp>

/**
* @brief Camera is a C struct, so we need to wrap it in a C++ class
*/

#if !defined(ZAP_CUSTOM_CAMERA)
    #define ZAP_NO_COMPUTE 0.f
    #define ZAP_PITCH_NULL 0.f
    #define ZAP_YAW_NULL 0.f
    #define ZAP_SPRINT_SPEED 2.5f
    #define ZAP_NO_SPRINT_SPEED 1.f
    #define ZAP_DEFAULT_SENSITIVITY 0.005f
    #define ZAP_ROTATION_AXIS {0.f, 1.f, 0.f}
#endif

/**
 * rcamera api call
 */

#if !defined(RCAMERA_H)
    #define RCAMERA_H

extern "C" {
RLAPI void CameraMoveForward(Camera *camera, float distance, bool moveInWorldPlane);
RLAPI void CameraMoveUp(Camera *camera, float distance);
RLAPI void CameraMoveRight(Camera *camera, float distance, bool moveInWorldPlane);
RLAPI void CameraMoveToTarget(Camera *camera, float delta);
RLAPI void CameraRoll(Camera *camera, float angle);
RLAPI void CameraYaw(Camera *camera, float angle, bool rotateAroundTarget);
RLAPI void CameraPitch(Camera *camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp);
}

#endif

/**
* public
*/

#include <iostream>

zap::ZapCamera::ZapCamera() noexcept
{
    _camera.position = {4.f, 4.f, 4.f};
    _camera.target = {0.f, 0.f, 0.f};
    _camera.up = {0.f, 1.f, 0.f};
    _camera.fovy = 70.f;
    _camera.projection = CAMERA_PERSPECTIVE;

    event::EventCallback::getInstance().add(KEY_P, [&]() { std::cout << "pos: " << _camera.position << std::endl; });
    event::EventCallback::getInstance().add(KEY_R, [&]() {
        _camera.position = {4.f, 4.f, 4.f};
        _camera.target = {0.f, 0.f, 0.f};
    });
}

/**
 * static helpers
 */

[[nodiscard]] static inline const Vector3 _get_forward(const Vector3 &target, const Vector3 &position) noexcept
{
    return Vector3Normalize(Vector3Subtract(target, position));
}

void zap::ZapCamera::update() noexcept
{
    const Vector2 delta = GetMouseDelta();
    const f32 time = GetFrameTime();

    const bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    const f32 move_speed = _move_speed * time * (shift ? ZAP_SPRINT_SPEED : ZAP_NO_SPRINT_SPEED);
    const f32 rotation_speed = _rotation_speed * time * (shift ? ZAP_SPRINT_SPEED : ZAP_NO_SPRINT_SPEED);

    CameraYaw(&_camera, -delta.x * _sensitivity, false);
    CameraPitch(&_camera, -delta.y * _sensitivity, true, false, false);

    if (IsKeyDown(KEY_Q)) {
        CameraRoll(&_camera, -rotation_speed);
    }
    if (IsKeyDown(KEY_E)) {
        CameraRoll(&_camera, rotation_speed);
    }
    if (IsKeyDown(KEY_W)) {
        CameraMoveForward(&_camera, move_speed, true);
    }
    if (IsKeyDown(KEY_A)) {
        CameraMoveRight(&_camera, -move_speed, true);
    }
    if (IsKeyDown(KEY_S)) {
        CameraMoveForward(&_camera, -move_speed, true);
    }
    if (IsKeyDown(KEY_D)) {
        CameraMoveRight(&_camera, move_speed, true);
    }
    if (IsKeyDown(KEY_SPACE)) {
        CameraMoveUp(&_camera, move_speed);
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        CameraMoveUp(&_camera, -move_speed);
    }
    CameraMoveToTarget(&_camera, -GetMouseWheelMove());
}

bool zap::ZapCamera::sees(const Vector3 &position) const noexcept
{
    const Vector3 to_target = Vector3Subtract(position, _camera.position);
    const Vector3 forward = _get_forward(_camera.target, _camera.position);
    const f32 dot = Vector3DotProduct(Vector3Normalize(to_target), forward);
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
