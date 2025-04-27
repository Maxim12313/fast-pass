#ifndef GAME_HPP
#define GAME_HPP

#include "input_system.hpp"
#include "player_body.hpp"
#include "timer.hpp"
#include <vector>

void runGame() {
    InitWindow(WIDTH, HEIGHT, "fast tag");

    InputSystem inputSystem;
    Timer timer;
    PlayerBody player1, player2;
    float deltaTime = 0;
    while (!WindowShouldClose()) {

        inputSystem.handlePlayer1(player1, deltaTime);
        inputSystem.handlePlayer2(player2, deltaTime);

        BeginDrawing();
        ClearBackground(DARKBROWN);
        player1.draw();
        player2.draw();
        timer.displayStats();

        EndDrawing();

        deltaTime = timer.updateOrWait();
    }

    CloseWindow();
}

#endif
