#include "raylib.h"
#include <iostream>

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - model animation");
    SetTargetFPS(60);

    // Camera FPS
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 4.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Load animated model and texture
    Model model = LoadModel("player.iqm");
    // Texture2D texture = LoadTexture("guytex.png");
    // model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    int animCount = 0;
    ModelAnimation* anims = LoadModelAnimations("playeranim.iqm", &animCount);

    if (anims == nullptr || animCount == 0) {
        std::cerr << "ERREUR: Animation introuvable ou non chargée.\n";
        UnloadModel(model);
        CloseWindow();
        return 1;
    }

    int animFrame = 0;

    Vector3 position = { 0.0f, 0.0f, 0.0f };

    while (!WindowShouldClose())
    {
        // Mise à jour de la caméra (mode FPS)
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        animFrame++;
        if (animFrame >= anims[0].frameCount) animFrame = 0;
        UpdateModelAnimation(model, anims[0], animFrame);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
            DisableCursor();
            DrawModel(model, position, 1.0f, BLACK);
            DrawGrid(10, 1.0f);
        EndMode3D();

        DrawText("Use WASD + Mouse to move", 10, 10, 20, DARKGRAY);
        DrawText("ESC to quit", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    // Nettoyage
    UnloadModel(model);
    // UnloadTexture(texture);
    UnloadModelAnimations(anims, animCount);
    CloseWindow();

    return 0;
}
