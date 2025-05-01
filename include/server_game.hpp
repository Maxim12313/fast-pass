#ifndef SERVER_GAME_HPP
#define SERVER_GAME_HPP

#include "config.hpp"
#include "player_system.hpp"
#include "server.hpp"
#include "timer.hpp"
#include <raylib.h>
#include <vector>

class ServerGame {
public:
    ServerGame(Server *server_in) : server(server_in) {}

    void run() {
        InitWindow(WIDTH, HEIGHT, "fast tag");
        while (!WindowShouldClose()) {

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
    Server *server;
    Timer timer;
    std::vector<PlayerBody> players;
};

#endif
