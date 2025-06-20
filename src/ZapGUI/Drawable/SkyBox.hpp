/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** SkyBox.hpp
*/

#pragma once

#define ZAP_USE_RAYLIB_RLGL
#define ZAP_USE_RAYLIB_MATH

#include <ZapGUI/Drawable.hpp>
#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Render/Camera.hpp>


namespace zap {

class SkyBox {
public:
    SkyBox(bool useHDR = false, const char* file = nullptr);
    ~SkyBox();

    void Draw();

    void LoadFromFile(const char* fileName);
    void ReloadDropped();

private:
    Model _model;
    Shader _shaderSkybox;
    Shader _shaderCubemap;
    Texture2D _panorama;
    bool _useHDR;
    char _currentFile[256];

    TextureCubemap GenCubemap(Shader shader, int size, int format);
};

}