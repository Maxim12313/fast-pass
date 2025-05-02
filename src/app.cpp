#include "../include/client.hpp"
#include "../include/game.hpp"
#include "../include/server.hpp"
#include "../include/structs.hpp"
#include <atomic>
#include <csignal>
#include <cstdio>
#include <iostream>

extern std::atomic<bool> running;

void signalHandler(int) {
    running = false;
}

void runServer() {
    Server server;
    Game game;
    serverGameLoop(game, server);
}

void runClient() {
    Game game;
    game.players.emplace_back(0);

    Client client;
    client.connect();
    client.handleEvent(game);
    clientGameLoop(game, 0, client);
}

int main(int argc, char **argv) {
    if (enet_initialize() != 0) {
        fprintf(stderr, "erorr while init enet\n");
        exit(1);
    }
    atexit(enet_deinitialize);
    std::signal(SIGINT, signalHandler);

    if (argc >= 2 && argv[1][0] == '1') {
        LOG("Running Server");
        runServer();
    } else {
        LOG("Running Client");
        runClient();
    }
}
