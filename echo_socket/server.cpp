#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main() {
    int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == -1) {
        perror("socket");
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    if (bind(listenSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("bind");
        close(listenSocket);
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) == -1) {
        perror("listen");
        close(listenSocket);
        return 1;
    }

    std::cout << "Server started, listening on port 8080..." << std::endl;

    fd_set readSet, allSet;
    FD_ZERO(&allSet);
    FD_SET(listenSocket, &allSet);
    int maxfd = listenSocket;

    while (true) {
        readSet = allSet;
        int ready = select(maxfd + 1, &readSet, NULL, NULL, NULL);
        if (ready == -1) {
            perror("select");
            break;
        }

        if (FD_ISSET(listenSocket, &readSet)) {
            sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientSocket = accept(listenSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
            if (clientSocket == -1) {
                perror("accept");
                continue;
            }

            std::cout << "Accepted connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

            FD_SET(clientSocket, &allSet);
            if (clientSocket > maxfd) {
                maxfd = clientSocket;
            }
        } else {
            char buffer[1024];
            int numBytes;

            // Find the client socket that has data to read
            for (int i = listenSocket + 1; i <= maxfd; ++i) {
                if (FD_ISSET(i, &readSet)) {
                    numBytes = recv(i, buffer, sizeof(buffer), 0);
                    if (numBytes <= 0) {
                        if (numBytes == 0) {
                            // Client disconnected
                            std::cout << "Client disconnected" << std::endl;
                        } else {
                            perror("recv");
                        }

                        close(i);
                        FD_CLR(i, &allSet);
                    } else {
                        // Echo back to the client
                        send(i, buffer, numBytes, 0);
                    }
                }
            }
        }
    }

    close(listenSocket);
    return 0;
}
