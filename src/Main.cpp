/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Main.cpp
*/

// clang-format off
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wundef"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wundef"
#endif
#include <raylib.h>
#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif
// clang-format on

int main(void)
{
    InitWindow(1920, 1080, "Zappy");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Welcome to Zappierdolekurwa!", 190, 280, 20, PURPLE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
