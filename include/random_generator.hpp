#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

#include "globals.hpp"
#include <cassert>
#include <cstdint>
#include <numeric>
#include <random>
#include <raylib.h>
#include <unordered_set>

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<int64_t> distrib(INT64_MIN, INT64_MAX);

struct IDGenerator {
    std::unordered_set<uint32_t> used;
    IDGenerator() {}

    uint32_t getId() {
        while (true) {
            uint32_t id = abs(distrib(gen)) % UINT32_MAX;
            if (!used.count(id)) {
                used.insert(id);
                return id;
            }
        }
    }
    void destroyId(uint32_t id) {
        auto it = used.find(id);
        if (it != end(used))
            used.erase(it);
    }
};

// upper bound exclusive
Vector2 getRandPos(int x1, int x2, int y1, int y2) {
    assert(x1 < x2 && "x1 < x2");
    assert(y1 < y2 && "x1 < x2");
    int x = x1 + (abs(distrib(gen)) % (x2 - x1));
    int y = y1 + (abs(distrib(gen)) % (y2 - y1));
    LOG("got " << x << " " << y);
    return Vector2(x, y);
}

#endif
