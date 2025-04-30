#include "../include/client_game.hpp"
#include <csignal>
#include <cstdio>
#include <enet/enet.h>
#include <iostream>

bool running = true;

void signalHandler(int) {
    running = false;
}

void test_client_basic() {
    if (enet_initialize() != 0) {
        fprintf(stderr, "erorr while init enet\n");
        exit(1);
    }
    atexit(enet_deinitialize);
    std::signal(SIGINT, signalHandler);

    Client client;
    client.connect();
    std::string msg;
    while (true) {
        std::getline(std::cin, msg);
        if (msg == "exit()")
            break;
        client.sendPacket(msg.c_str(), msg.size() + 1);
        client.handleEvent();
    }
}

void test_pos_send_read() {
    char buffer[1024];
    Vector2 pos(10, 20);
    setPos(buffer, pos);
    Vector2 res = readPos(&buffer[1]);
    std::cout << res.x << " " << res.y << "\n";
}

int main() {
}
