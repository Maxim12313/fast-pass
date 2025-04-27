#include "../include/game_client.hpp"
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

    GameClient client;
    client.connect();

    std::string msg;
    while (running) {
        std::getline(std::cin, msg);
        if (msg == "exit()")
            break;
        client.sendPacket(msg.c_str());
        client.handleEvent();
    }
}
