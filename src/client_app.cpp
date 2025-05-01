#include "../include/client.hpp"
#include "../include/game.hpp"
#include "../include/structs.hpp"
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

    Game game;
    game.players.emplace_back(0);

    Client client;
    client.connect();
    client.handleEvent(game);
    clientGameLoop(game, 0, client);
}
