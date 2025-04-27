#ifndef CLIENT_GAME_HPP
#define CLIENT_GAME_HPP

#include "client.hpp"
#include "config.hpp"
#include "game.hpp"
#include "player_system.hpp"
#include "timer.hpp"
#include <raylib.h>
#include <vector>

class ClientGame {
public:
    ClientGame(Client *client_in) : client(client_in) {
        playerSystem.addPlayer(0);
    }

    void run() {
        InitWindow(WIDTH, HEIGHT, "fast tag");
        while (!WindowShouldClose()) {
            playerSystem.input(0, timer.deltaTime);

            BeginDrawing();
            ClearBackground(DARKBROWN);
            playerSystem.draw();
            timer.displayStats();
            EndDrawing();

            timer.updateOrWait();
        }
        CloseWindow();
    }

private:
    Client *client;
    Timer timer;
    PlayerSystem playerSystem;
};

#endif
