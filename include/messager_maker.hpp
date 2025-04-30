#ifndef MESSAGE_MAKER_HPP
#define MESSAGE_MAKER_HPP

#include "player_system.hpp"
#include <bit>
#include <cstdint>
#include <cstring>

enum NetworkOpcode {
    SEND_POS = 0,
};

// asssume opcode already read and msg[0] is first byte to read
Vector2 readPos(char *msg) {
    Vector2 pos(0, 0);
    uint32_t offset = 0;
    std::memcpy(&pos.x, &msg[offset], sizeof(float));
    offset += sizeof(float);
    std::memcpy(&pos.y, &msg[offset], sizeof(float));
    offset += sizeof(float);
    return pos;
}

// returns size
uint32_t setPos(char *msg, Vector2 &pos) {
    uint32_t offset = 0;

    msg[offset++] = SEND_POS;
    std::memcpy(&msg[offset], &pos.x, sizeof(float));
    offset += sizeof(float);
    std::memcpy(&msg[offset], &pos.y, sizeof(float));
    offset += sizeof(float);
    msg[offset] = '\0';

    return offset;
}

uint64_t addBits(uint32_t input, uint32_t add) {
    uint32_t width = std::bit_width<uint32_t>(add);
    return (input << width) | add;
}

#endif
