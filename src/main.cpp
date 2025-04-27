#include "../include/client_game.hpp"
#include <csignal>
#include <cstdio>
#include <enet/enet.h>

bool running = true;

void signalHandler(int) {
    running = false;
}

void testClient() {
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
        client.sendPacket(msg.c_str());
        client.handleEvent();
    }
}
void testClientGame() {
    // ClientGame game;
    // game.run();
}

int main() {
    testClientGame();
}
