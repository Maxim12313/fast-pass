#ifndef GAME_HPP
#define GAME_HPP

#include "client.hpp"
#include "config.hpp"
#include "player_system.hpp"
#include "timer.hpp"
#include <raylib.h>
#include <vector>

struct Game {
    Timer timer;
    PlayerSystem playerSystem;
};

#endif
