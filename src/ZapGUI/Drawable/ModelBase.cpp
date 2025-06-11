/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** ModelBase.cpp
*/

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

void zap::abstract::ModelBase::setScale(const Vector3 &scale)
{
    _scale = scale;
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
