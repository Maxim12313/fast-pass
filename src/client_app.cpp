#include "../include/client.hpp"
#include "../include/client_game.hpp"
#include <csignal>
#include <cstdio>

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
    ClientGame game(&client);
    game.run();
}
