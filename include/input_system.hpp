#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

#include "player.hpp"
#include <iostream>
#include <raymath.h>

struct InputSystem {
    void handlePlayer(Player &p, float deltaTime) {
        Vector2 change(0, 0);
        if (IsKeyDown(KEY_D))
            change.x++;
        if (IsKeyDown(KEY_A))
            change.x--;
        if (IsKeyDown(KEY_W))
            change.y--;
        if (IsKeyDown(KEY_S))
            change.y++;

        if (IsKeyPressed(KEY_Q))
            p.isMenu ^= 1;

        Vector2 *pos;
        float speed;
        if (p.isMenu) {
            pos = &p.cursor.pos;
            speed = p.cursor.speed;
        } else {
            pos = &p.body.pos;
            speed = p.body.speed;
        }

        change = Vector2Scale(Vector2Normalize(change), speed * deltaTime);
        *pos = Vector2Add(*pos, change);
    }
};

#endif
