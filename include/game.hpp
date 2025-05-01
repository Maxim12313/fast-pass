#ifndef GAME_HPP
#define GAME_HPP

#include "client.hpp"
#include "config.hpp"
#include "player_system.hpp"
#include "timer.hpp"
#include <raylib.h>
#include <vector>

void clientGameLoop(Game &g, int curr, Client &client) {
    PlayerBody &currPlayer = g.players[curr];

    InitWindow(WIDTH, HEIGHT, "fast tag");
    while (!WindowShouldClose()) {
        playerInput(currPlayer, g.timer.deltaTime);

        BeginDrawing();

        ClearBackground(DARKBROWN);
        playersDraw(g);

        EndDrawing();

        client.sendPos(currPlayer.pos);

        g.timer.updateOrWait();
    }
    CloseWindow();
}

#endif
