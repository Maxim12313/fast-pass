#include <csignal>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

bool volatile running = true;
int clientSocket;

void signalHandler(int) {
    std::cout << "\nshutting down\n";
    close(clientSocket);
}

int main() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    std::signal(SIGINT, signalHandler);

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
