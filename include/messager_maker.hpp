#ifndef MESSAGE_MAKER_HPP
#define MESSAGE_MAKER_HPP

#include "globals.hpp"
#include "player_system.hpp"
#include <arpa/inet.h>
#include <bit>
#include <cstdint>
#include <cstring>

enum NetworkOpcode {
    SEND_POS = 0,
    SEND_ALL_POS,
};

template <typename T>
static inline void setParam(char *msg, uint32_t &offset, T *ptr) {
    std::memcpy(&msg[offset], ptr, sizeof(T));
    offset += sizeof(T);
}

template <typename T>
static inline void getParam(T *ptr, char *msg, uint32_t &offset) {
    std::memcpy(ptr, &msg[offset], sizeof(T));
    offset += sizeof(T);
}

static int16_t toNetworkInt(float val) {
    int16_t data = int16_t(val * SERVER_PRECISION);
    // just interpret as unsigned for sake of htons
    uint16_t raw = std::bit_cast<int16_t>(data);
    return htons(raw);
}

static float fromNetworkInt(int16_t val) {
    uint16_t raw = ntohs(val);
    // just interpret as unsigned for sake of htons
    int16_t data = std::bit_cast<int16_t>(raw);
    return float(data) / SERVER_PRECISION;
}

// returns bytes read
uint32_t readPos(Vector2 &pos, char *msg) {
    uint32_t offset = 0;

    int16_t x;
    getParam(&x, msg, offset);

    int16_t y;
    getParam(&y, msg, offset);

    pos.x = fromNetworkInt(x);
    pos.y = fromNetworkInt(y);

    return sizeof(Vector2);
}

// returns size
uint32_t setPos(char *msg, Vector2 &pos) {
    uint32_t offset = 0;
    msg[offset++] = SEND_POS;

    int16_t x = toNetworkInt(pos.x);
    setParam(msg, offset, &x);

    int16_t y = toNetworkInt(pos.y);
    setParam(msg, offset, &y);

    return offset;
}

// returns size
uint32_t setAllPos(char *msg, Game &g) {
    uint32_t offset = 0;
    msg[offset++] = SEND_ALL_POS;

    int8_t entryCount = g.players.size();
    setParam(msg, offset, &entryCount);
    for (PlayerBody &body : g.players) {
        offset += setPos(&msg[offset], body.pos);
    }

    return offset;
}

// assume opcode already read
int32_t readAllPos(char *msg, std::vector<PlayerBody> &data) {
    uint32_t offset = 0;

    int8_t entryCount;
    getParam(&entryCount, msg, offset);
    assert(entryCount >= 1 && entryCount <= MAX_PLAYERS &&
           "too many or too few players");

    data.resize(entryCount);
    for (int i = 0; i < entryCount; i++) {
    }

    return offset;
}

#endif
