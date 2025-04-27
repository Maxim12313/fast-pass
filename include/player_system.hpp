#ifndef PLAYER_SYSTEM_HPP
#define PLAYER_SYSTEM_HPP

#include <cstdint>
#include <raylib.h>
#include <raymath.h>
#include <unordered_map>
#include <vector>

struct PlayerBody {
    Vector2 pos = {0, 0};
    float radius = 50;
    float speed = 1000;
    Color color = GRAY;
};

class PlayerSystem {
public:
    PlayerSystem() {}

    void addPlayer(int id) {
        idToIdx[id] = bodies.size();
        bodies.emplace_back();
    }

    void input(int id, float deltaTime) {
        Vector2 change(0, 0);
        if (IsKeyDown(KEY_D))
            change.x++;
        if (IsKeyDown(KEY_A))
            change.x--;
        if (IsKeyDown(KEY_W))
            change.y--;
        if (IsKeyDown(KEY_S))
            change.y++;

        PlayerBody &p = bodies[idToIdx[id]];
        change = Vector2Scale(Vector2Normalize(change), p.speed * deltaTime);
        p.pos = Vector2Add(p.pos, change);
    }

    void draw() {
        for (PlayerBody &p : bodies) {
            DrawCircle(p.pos.x, p.pos.y, p.radius - 10, p.color);
            DrawCircleLines(p.pos.x, p.pos.y, p.radius, p.color);
        }
    }

public:
    std::vector<PlayerBody> bodies;
    std::unordered_map<uint32_t, uint32_t> idToIdx;
    int64_t currPlayer = 0;
};

#endif
