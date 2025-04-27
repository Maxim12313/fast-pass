#ifndef SERVER_GAME_HPP
#define SERVER_GAME_HPP

#include "client.hpp"
#include "config.hpp"
#include "player_system.hpp"
#include "timer.hpp"
#include <raylib.h>
#include <vector>

class ClientGame {
public:
    enum State {
        Lobby,
        Playing,
    };

    ClientGame() { playerSystem.addPlayer(0); }

    void update() { playerSystem.input(timer.deltaTime); }

    void draw() {
        BeginDrawing();
        ClearBackground(DARKBROWN);
        playerSystem.draw();
        timer.displayStats();
        EndDrawing();
    }

    void run() {
        InitWindow(WIDTH, HEIGHT, "fast tag");
        while (!WindowShouldClose()) {
            update();
            draw();
            timer.updateOrWait();
        }
        CloseWindow();
    }

private:
    Timer timer;
    PlayerSystem playerSystem;
    State state = Lobby;
    Client *client;
};

#endif
