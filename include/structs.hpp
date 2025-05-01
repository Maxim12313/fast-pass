#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include "timer.hpp"
#include <cstdint>
#include <vector>

struct PlayerBody {
    uint8_t id = 0;
    Vector2 pos = {0, 0};
    float radius = 50;
    float speed = 1000;
    Color color = GRAY;
    PlayerBody(int id_in) : id(id_in) {}
};

struct Game {
    Timer timer;
    std::vector<PlayerBody> players;
};

#endif
