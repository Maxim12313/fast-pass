#include "../include/server.hpp"
#include <csignal>

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

    Server server;
    while (running) {
        server.handleEvent();
    }
}
