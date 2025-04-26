#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

#include "player_body.hpp"
#include <iostream>
#include <raymath.h>

struct InputSystem {
    void handlePlayer(PlayerBody &p, float deltaTime) {
        Vector2 change(0, 0);
        if (IsKeyDown(KEY_D))
            change.x++;
        if (IsKeyDown(KEY_A))
            change.x--;
        if (IsKeyDown(KEY_W))
            change.y--;
        if (IsKeyDown(KEY_S))
            change.y++;

        change = Vector2Scale(Vector2Normalize(change), p.speed * deltaTime);
        p.pos = Vector2Add(p.pos, change);
    }
};

#endif
