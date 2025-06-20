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

#define ZAP_NO_COMPUTE 0.f
#define ZAP_PITCH_NULL 0.f
#define ZAP_YAW_NULL 0.f
#define ZAP_DEFAULT_SENSITIVITY 0.005f
#define ZAP_ROTATION_AXIS {0.0f, 1.0f, 0.0f}

/**
 * rcamera api call
 */

extern "C" {
RLAPI void CameraMoveForward(Camera *camera, float distance, bool moveInWorldPlane);
RLAPI void CameraMoveUp(Camera *camera, float distance);
RLAPI void CameraMoveRight(Camera *camera, float distance, bool moveInWorldPlane);
RLAPI void CameraMoveToTarget(Camera *camera, float delta);
RLAPI void CameraRoll(Camera *camera, float angle);
}

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

/**
 * static helpers
 */

[[nodiscard]] static inline const Vector3 _get_forward(const Vector3 &target, const Vector3 &position) noexcept
{
    return Vector3Normalize(Vector3Subtract(target, position));
}

/**
 * public update events method
 */

void zap::ZapCamera::update() noexcept
{
    const Vector2 delta = GetMouseDelta();
    const f32 time = GetFrameTime();

    const f32 move_speed = _move_speed * time;
    const f32 rotation_speed = _rotation_speed * time;
    const f32 camera_pan_speed = _pan_speed * time;

    if (delta.x > ZAP_NO_COMPUTE) {
        CameraMoveRight(&_camera, camera_pan_speed, true);
    }
    if (delta.x < -ZAP_NO_COMPUTE) {
        CameraMoveRight(&_camera, -camera_pan_speed, true);
    }
    if (delta.y > ZAP_NO_COMPUTE) {
        CameraMoveUp(&_camera, -camera_pan_speed);
    }
    if (delta.y < -ZAP_NO_COMPUTE) {
        CameraMoveUp(&_camera, camera_pan_speed);
    }
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
