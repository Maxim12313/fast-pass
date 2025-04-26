#include <csignal>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

std::vector<std::thread> threads;
std::vector<int> clientSockets;

int serverSocket;

void signalHandler(int) {
    std::cout << "\nshutting down\n";
    close(serverSocket);
    for (int client : clientSockets)
        shutdown(client, SHUT_RD);
}

void handleUser(int clientSocket) {
    char buffer[1024] = {0};
    while (true) {
        ssize_t received = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (received <= 0)
            break;
        buffer[received] = '\0';
        std::cout << "message from client " << clientSocket << ": " << buffer
                  << "\n";
    }
    close(clientSocket);
}

int main() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    bind(serverSocket, (struct sockaddr *)&serverAddress,
         sizeof(serverAddress));
    listen(serverSocket, 5);

    std::signal(SIGINT, signalHandler);

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1)
            break;
        threads.emplace_back(handleUser, clientSocket);
        clientSockets.push_back(clientSocket);
    }
    for (std::thread &t : threads) {
        t.join();
    }
}
