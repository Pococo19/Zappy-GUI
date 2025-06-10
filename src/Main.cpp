/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Main.cpp
*/

#include <memory>

#include <ZapGUI/Drawable/Model.hpp>
#include <ZapGUI/Raylib.hpp>

int main(void)
{
    InitWindow(1920, 1080, "Zappy");

    std::unique_ptr<zap::abstract::Drawable> model = std::make_unique<zap::ZapModel>("assets/models/CommonTree_1.obj", "assets/textures/");

    Camera camera;
    camera.position = {4.0f, 4.0f, 4.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
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
