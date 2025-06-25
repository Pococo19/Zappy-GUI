/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ModelBase.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <ZapGUI/Drawable/ModelBase.hpp>
#include <ZapGUI/Error.hpp>
#include <ZapGUI/Filename.hpp>
#include <ZapGUI/Logger.hpp>

/**
* public setters and getters
*/

void zap::abstract::ModelBase::setPosition(const Vector3 &position)
{
    _position = position;
}

Vector3 zap::abstract::ModelBase::getPosition() const
{
    return _position;
}

void zap::abstract::ModelBase::setScale(const f32 scale)
{
    _scale = {scale, scale, scale};
}

void zap::abstract::ModelBase::setShader(const Shader &shader)
{
    if (shader.id == 0) {
        return;
    }
    _model.materials[0].shader = shader;
}

void zap::abstract::ModelBase::setScale(const Vector3 &scale)
{
    _scale = scale;
}

void zap::abstract::ModelBase::setRotation(const Vector3 &rotation)
{
    _rotationAxis = rotation;
}

Vector3 zap::abstract::ModelBase::getScale() const
{
    return _scale;
}

void zap::abstract::ModelBase::setTint(const Color &tint)
{
    _tint = tint;
}

Color zap::abstract::ModelBase::getTint() const
{
    return _tint;
}

void zap::abstract::ModelBase::setRotationAxis(const Vector3 &axis, const f32 angle)
{
    _rotationAxis = axis;
    _rotationAngle = angle;
}

Matrix zap::abstract::ModelBase::getTransform() const
{
    Matrix transform = MatrixIdentity();

    const Matrix scale = MatrixScale(_scale.x, _scale.y, _scale.z);
    const Matrix rotation = MatrixRotate(_rotationAxis, _rotationAngle * DEG2RAD);
    const Matrix translation = MatrixTranslate(_position.x, _position.y, _position.z);

    /** @brief T * R * S */
    transform = MatrixMultiply(scale, rotation);
    transform = MatrixMultiply(transform, translation);

    return transform;
}
