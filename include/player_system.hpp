#ifndef PLAYER_SYSTEM_HPP
#define PLAYER_SYSTEM_HPP

#include "structs.hpp"
#include <cstdint>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <unordered_map>
#include <vector>

void playerInput(PlayerBody &player, float deltaTime) {
    Vector2 change(0, 0);
    if (IsKeyDown(KEY_D))
        change.x++;
    if (IsKeyDown(KEY_A))
        change.x--;
    if (IsKeyDown(KEY_W))
        change.y--;
    if (IsKeyDown(KEY_S))
        change.y++;

    if (Vector2Length(change) == 0)
        return;

    change = Vector2Scale(Vector2Normalize(change), player.speed * deltaTime);
    player.pos = Vector2Add(player.pos, change);
    // send their key strokes
}

void playersDraw(Game &g) {
    for (PlayerBody &p : g.players) {
        DrawCircle(p.pos.x, p.pos.y, p.radius - 10, p.color);
        DrawCircleLines(p.pos.x, p.pos.y, p.radius, p.color);
    }
}
#endif
