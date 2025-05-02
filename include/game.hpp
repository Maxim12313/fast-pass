#ifndef GAME_HPP
#define GAME_HPP

#include "client.hpp"
#include "globals.hpp"
#include "player_system.hpp"
#include "server.hpp"
#include "stats.hpp"
#include <raylib.h>
#include <vector>

extern std::atomic<bool> running;

void serverGameLoop(Game &g, Server &server) {
    InitWindow(WIDTH, HEIGHT, "fast tag server");
    while (running) {
        server.handleEvent(g);

        BeginDrawing();

        ClearBackground(DARKBROWN);
        playersDraw(g);

        EndDrawing();
    }
    CloseWindow();
}

void clientGameLoop(Game &g, int curr, Client &client) {
    PlayerBody &currPlayer = g.players[curr];

    InitWindow(WIDTH, HEIGHT, "fast tag client");
    Vector2 prevPos = currPlayer.pos;
    float deltaTime = 0;
    while (!WindowShouldClose() && running) {
        playerInput(currPlayer, deltaTime);

        BeginDrawing();

        ClearBackground(DARKBROWN);
        playersDraw(g);
        displayStats(deltaTime);

        EndDrawing();

        if (prevPos != currPlayer.pos) {
            client.sendPos(currPlayer.pos);
            prevPos = currPlayer.pos;
        }

        deltaTime = GetFrameTime();
    }
    CloseWindow();
}

#endif
