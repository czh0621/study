//
// Created by viruser on 2023/7/22.
//

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>
#include <condition_variable>

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("socket");
        return 1;
    }
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with the server IP address
    serverAddr.sin_port = htons(8080); // Replace with the server port number

    if (connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
        perror("connect1");
        close(clientSocket);
        return 1;
    }
    int flag = false;
    std::cout << "Connected to server" << std::endl;
    int flags = fcntl(clientSocket, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(clientSocket, F_SETFL, flags);
    while (true) {
        fd_set readSet, writeSet;
        FD_ZERO(&readSet);
        FD_ZERO(&writeSet);
        FD_SET(STDIN_FILENO, &readSet);
        FD_SET(clientSocket, &readSet);
        if (flag) {
            FD_SET(clientSocket, &writeSet);
        }


        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        int maxfd = std::max(STDIN_FILENO, clientSocket) + 1;
        int ready = select(maxfd, &readSet, &writeSet, NULL, &timeout);
        std::cout<<"reeady ret "<<ready<<std::endl;
        if (ready == -1) {
            perror("select");
            break;
        } else if (ready == 0) {
            // Timeout
            std::cout << "select timeout" << timeout.tv_sec << std::endl;
            continue;
        }

        // Check for standard input data to send
        if (FD_ISSET(STDIN_FILENO, &readSet)) {
            std::cout << "SELECT STD_IN " << ready << std::endl;
            char buffer[1024];
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                int len = strlen(buffer);
                if (send(clientSocket, buffer, len, 0) == -1) {
                    perror("send");
                    close(clientSocket);
                    return 1;
                }
            } else {
                // Error or EOF on stdin
                break;
            }
            flag = true;
        }

        // Check for data to receive from the server
        if (FD_ISSET(clientSocket, &readSet)) {
            std::cout << "SELECT readSet " << ready << std::endl;
            char buffer[1024];
            int numBytes = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (numBytes > 0) {
                std::cout << "Received: " << std::string(buffer, numBytes);
            } else if (numBytes == 0) {
                // Server disconnected
                std::cout << "Server disconnected" << std::endl;
                break;
            } else {
                perror("recv");
                break;
            }

        }

        // Check for any pending data in the send buffer
        if (FD_ISSET(clientSocket, &writeSet)) {
            // Here you can handle any special processing after the data is sent
            // ...
//            std::cout<<"SELECT writeSet "<<ready<<std::endl;
        }
    }
    while(1){
        f();
    }

    return 0;
}


