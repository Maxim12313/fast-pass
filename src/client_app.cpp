#include "../include/client.hpp"
#include "../include/client_game.hpp"
#include <csignal>
#include <cstdio>
#include <iostream>

bool running = true;

void signalHandler(int) {
    running = false;
}

int main() {
    if (enet_initialize() != 0) {
        fprintf(stderr, "erorr while init enet\n");
        exit(1);
    }
    atexit(enet_deinitialize);
    std::signal(SIGINT, signalHandler);

    Client client;
    client.connect();
    PlayerBody player(0);
    player.pos = Vector2{10, 20};
    client.sendPos(player.pos);
}
