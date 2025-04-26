#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "cursor.hpp"
#include "player_body.hpp"

struct Player {
    PlayerBody body;
    Cursor cursor;
    bool isMenu = false;

    Player() : cursor(body.radius) {}

    void draw() const {
        if (isMenu)
            cursor.draw();
        else
            body.draw();
    }
};

#endif
