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
inline void setParam(char *msg, uint32_t &offset, T *ptr) {
    std::memcpy(&msg[offset], ptr, sizeof(T));
    offset += sizeof(T);
}

template <typename T>
inline void getParam(T *ptr, char *msg, uint32_t &offset) {
    std::memcpy(ptr, &msg[offset], sizeof(T));
    offset += sizeof(T);
}

int16_t toNetworkInt(float val) {
    // just interpret as unsigned for sake of htons
    int16_t data = int16_t(val * SERVER_PRECISION);
    uint16_t raw = *reinterpret_cast<uint16_t *>(&data);
    return htons(raw);
}

float fromNetworkInt(int16_t val) {
    uint16_t raw = ntohs(val);
    int16_t data = *reinterpret_cast<int16_t *>(&raw);
    return float(data) / SERVER_PRECISION;
}

// asssume opcode already read and msg[0] is first byte to read
Vector2 readPos(char *msg) {
    uint32_t offset = 0;

    int16_t x;
    getParam(&x, msg, offset);

    int16_t y;
    getParam(&y, msg, offset);

    Vector2 pos(fromNetworkInt(x), fromNetworkInt(y));

    LOG("reading: " << pos.x << " " << pos.y);

    return pos;
}

// returns size
uint32_t setPos(char *msg, Vector2 &pos) {
    uint32_t offset = 0;
    msg[offset++] = SEND_POS;

    int16_t x = toNetworkInt(pos.x);
    setParam(msg, offset, &x);

    int16_t y = toNetworkInt(pos.y);
    setParam(msg, offset, &y);

    LOG("setting: " << pos.x << " " << pos.y);

    return offset;
}

// void setAllPos(char *msg, Game &g) {
//     uint32_t offset = 0;
//     msg[offset++] = SEND_ALL_POS;
//
//     int8_t entryCount = g.players.size();
//     std::memcpy(&msg[offset], &entryCount, sizeof(entryCount));
//     offset += entryCount;
//
//     for (PlayerBody &body : g.players) {
//         offset += setPos(&msg[offset], body.pos);
//     }
// }
//
// void readAllPos() {
// }

#endif
