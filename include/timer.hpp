#ifndef TIMER_HPP
#define TIMER_HPP

#include <raylib.h>

struct Timer {
    double prev = 0;
    int targetFPS = 60;
    float deltaTime = 0;

    void displayStats() const {
        DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f / deltaTime)),
                 GetScreenWidth() - 220, 40, 20, GREEN);
    }

    float updateOrWait() {
        double spent = GetTime() - prev;
        double wait = (1.0 / targetFPS) - spent;
        if (wait > 0.0)
            WaitTime(wait);

        double curr = GetTime();
        deltaTime = curr - prev;
        prev = curr;
        return deltaTime;
    }
};

#endif
