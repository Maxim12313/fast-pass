#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

#include <cstdint>
#include <numeric>
#include <random>
#include <unordered_set>

static std::random_device rd;
static std::mt19937 gen(rd());

struct IDGenerator {
    std::unordered_set<uint32_t> used;
    std::uniform_int_distribution<uint32_t> distrib;
    IDGenerator() : distrib(0, UINT32_MAX) {}

    uint32_t getId() {
        while (true) {
            uint32_t id = distrib(gen);
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

#endif
