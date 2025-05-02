#ifndef CURSOR_HPP
#define CURSOR_HPP

#include "globals.hpp"
#include <raylib.h>

struct Cursor {
    Vector2 pos;
    float speed = 1000;
    float scale = 3;
    int radius;

    Cursor(int rad) : pos(WIDTH / 2, HEIGHT / 2), radius(rad) {}

    void draw() const {
        DrawCircle(pos.x, pos.y, (radius - 10) / scale, GRAY);
        DrawCircleLines(pos.x, pos.y, radius / scale, GRAY);
    }
};

#endif
