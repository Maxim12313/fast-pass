#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP
#include <csignal>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

class GameClient {
public:
    GameClient() {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(8080);
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        connect(clientSocket, (struct sockaddr *)&serverAddr,
                sizeof(serverAddr));
    }

    void run() {
        std::string msg;
        while (true) {
            std::getline(std::cin, msg);
            ssize_t res = send(clientSocket, msg.c_str(), msg.size(), 0);
            if (res == -1) {
                close(clientSocket);
                break;
            }
        }
    }

    void clientShutdown() { close(clientSocket); }

private:
    int clientSocket;
};

#endif
