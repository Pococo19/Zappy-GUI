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

static inline void _rotate_camera(Vector3 *up, const Vector3 &forward, f32 angle) noexcept
{
    if (angle == ZAP_NO_COMPUTE) {
        return;
    }
    const Matrix rot = MatrixRotate(forward, angle);

    *up = Vector3Transform(*up, rot);
}

static inline void _advance_camera(Vector3 *position, const Vector3 &forward, f32 speed) noexcept
{
    if (speed == ZAP_NO_COMPUTE) {
        return;
    }
    *position = Vector3Add(*position, Vector3Scale(forward, speed));
}

static inline void _strafe_camera(Vector3 *position, const Vector3 &up, const Vector3 &forward, f32 speed) noexcept
{
    if (speed == ZAP_NO_COMPUTE) {
        return;
    }
    const Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, up));

    *position = Vector3Add(*position, Vector3Scale(right, speed));
}

static void _keybord_events(Vector3 *up, Vector3 *position, const Vector3 &forward) noexcept
{
    constexpr f32 rotation_speed = 0.025f;
    constexpr f32 movement_speed = 0.1f;

    if (IsKeyDown(KEY_Q)) {
        _rotate_camera(up, forward, -rotation_speed);
    }
    if (IsKeyDown(KEY_E)) {
        _rotate_camera(up, forward, rotation_speed);
    }
    if (IsKeyDown(KEY_W)) {
        _advance_camera(position, forward, movement_speed);
    }
    if (IsKeyDown(KEY_S)) {
        _advance_camera(position, forward, -movement_speed);
    }
    if (IsKeyDown(KEY_A)) {
        _strafe_camera(position, *up, forward, -movement_speed);
    }
    if (IsKeyDown(KEY_D)) {
        _strafe_camera(position, *up, forward, movement_speed);
    }
}

/**
 * public update events method
 */

void zap::ZapCamera::update() noexcept
{
    Vector3 forward = _get_forward(_camera.target, _camera.position);
    Vector3 up = _camera.up;

    const Vector2 mouse_delta = GetMouseDelta();
    constexpr f32 sensitivity = ZAP_DEFAULT_SENSITIVITY;
    const f32 yaw = -mouse_delta.x * sensitivity;
    const f32 pitch = -mouse_delta.y * sensitivity;

    if (yaw != ZAP_YAW_NULL) {
        const Matrix rot = MatrixRotate(ZAP_ROTATION_AXIS, yaw);

        forward = Vector3Transform(forward, rot);
        up = Vector3Transform(up, rot);
    }

    if (pitch != ZAP_PITCH_NULL) {
        const Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, up));
        const Matrix rot = MatrixRotate(right, pitch);

        forward = Vector3Transform(forward, rot);
        up = Vector3Transform(up, rot);
    }

    _keybord_events(&up, &_camera.position, forward);

    _camera.target = Vector3Add(_camera.position, forward);
    _camera.up = up;
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
