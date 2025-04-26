#ifndef PLAYER_BODY_HPP
#define PLAYER_BODY_HPP

#include "config.hpp"
#include <raylib.h>

struct PlayerBody {
    Vector2 pos;
    float speed = 500;
    float radius = 50;

    PlayerBody() : pos(WIDTH / 2, HEIGHT / 2) {}

    void draw() const {
        // int x = WIDTH / 2;
        // int y = HEIGHT / 2;
        DrawCircle(pos.x, pos.y, radius - 10, GRAY);
        DrawCircleLines(pos.x, pos.y, radius, GRAY);
    }
};

#endif
