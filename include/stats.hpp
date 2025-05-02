#pragma once

#include <raylib.h>

void displayStats(float deltaTime) {
    DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f / deltaTime)),
             GetScreenWidth() - 220, 40, 20, GREEN);
}
