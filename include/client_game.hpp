#ifndef CLIENT_GAME_HPP
#define CLIENT_GAME_HPP

#include "client.hpp"
#include "config.hpp"
#include "player_system.hpp"
#include "timer.hpp"
#include <raylib.h>
#include <vector>

class ClientGame {
public:
    ClientGame(Client *client_in) : currPlayer(0), client(client_in) {}

    void run() {
        InitWindow(WIDTH, HEIGHT, "fast tag");
        while (!WindowShouldClose()) {
            playersInput(currPlayer, timer.deltaTime);

            BeginDrawing();
            ClearBackground(DARKBROWN);
            playersDraw(players);
            timer.displayStats();
            EndDrawing();

            timer.updateOrWait();
        }
        CloseWindow();
    }

private:
    Client *client;
    Timer timer;

    std::vector<PlayerBody> players;
    PlayerBody currPlayer;
};

#endif
