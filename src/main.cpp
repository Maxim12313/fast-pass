#include "../include/config.hpp"
#include <raylib.h>

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "fast tag");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("my cool window", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
