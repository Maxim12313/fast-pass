#ifndef GAME_HPP
#define GAME_HPP

#include "client.hpp"
#include "globals.hpp"
#include "player_system.hpp"
#include "server.hpp"
#include "timer.hpp"
#include <raylib.h>
#include <vector>

extern std::atomic<bool> running;

void serverGameLoop(Game &g, Server &server) {
    while (running) {
        server.handleEvent(g);
    }
}

void clientGameLoop(Game &g, int curr, Client &client) {
    PlayerBody &currPlayer = g.players[curr];

    InitWindow(WIDTH, HEIGHT, "fast tag");
    Vector2 prevPos = currPlayer.pos;
    while (!WindowShouldClose() && running) {
        playerInput(currPlayer, g.timer.deltaTime);
        playersDraw(g);

        BeginDrawing();

        ClearBackground(DARKBROWN);

        EndDrawing();

        if (prevPos != currPlayer.pos) {
            client.sendPos(currPlayer.pos);
            prevPos = currPlayer.pos;
        }

        g.timer.updateOrWait();
    }
    CloseWindow();
}

#endif
