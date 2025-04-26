#include "../include/game_client.hpp"

GameClient *client;

void signalHandler(int) {
    std::cout << "\nshutting down\n";
    client->clientShutdown();
}

int main() {
    GameClient c;
    client = &c;
    client->run();
}
