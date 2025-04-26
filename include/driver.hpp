#ifndef RUN_HPP
#define RUN_HPP

#include "input_system.hpp"
#include "player_body.hpp"
#include "timer.hpp"

void runGame() {
    InitWindow(WIDTH, HEIGHT, "fast tag");

    InputSystem inputSystem;
    Timer timer;
    PlayerBody player;
    float deltaTime = 0;
    while (!WindowShouldClose()) {

        inputSystem.handlePlayer(player, deltaTime);

        BeginDrawing();
        ClearBackground(DARKBROWN);

        player.draw();
        timer.displayStats();

        EndDrawing();

        deltaTime = timer.updateOrWait();
    }

    CloseWindow();
}

#endif
