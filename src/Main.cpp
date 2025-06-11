/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Main.cpp
*/

#include "ZapGUI/Render/Camera.hpp"
#include <memory>

#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Raylib.hpp>

int main(void)
{
    InitWindow(1920, 1080, "Zappy");

    std::unique_ptr<zap::abstract::Drawable> model = std::make_unique<zap::ZapModel>("assets/models/CommonTree_1.obj", "assets/textures/");
    zap::ZapCamera camera;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        camera.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera.get());
        model->draw();
        DrawGrid(10, 1.0f);
        EndMode3D();

        DrawText("ESC to leave", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    model.reset();
    CloseWindow();

    return 0;
}
