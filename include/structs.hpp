#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include "globals.hpp"
#include "random_generator.hpp"
#include "timer.hpp"
#include <cstdint>
#include <raylib.h>
#include <vector>

struct PlayerBody {
    uint8_t id = 0;
    Vector2 pos;
    float radius = 50;
    float speed = 1000;
    Color color = GRAY;
    PlayerBody(int id_in) : id(id_in) { pos = getRandPos(0, WIDTH, 0, HEIGHT); }
};

struct Game {
    Timer timer;
    std::vector<PlayerBody> players;
};

#endif
