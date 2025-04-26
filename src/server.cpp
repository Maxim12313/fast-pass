#include "../include/game_server.hpp"
#include <csignal>

GameServer *server;

void signalHandler(int) {
    if (server)
        server->serverShutdown();
}

int main() {
    std::signal(SIGINT, signalHandler);
    GameServer s;
    server = &s;

    server->run();
}
