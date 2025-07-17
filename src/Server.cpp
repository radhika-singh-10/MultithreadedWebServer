#include "Server.h"
#include "RequestHandler.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

/**
 * @brief Server constructor
 * @param port The port number to listen on
 * @param poolSize The size of the thread pool
 */
Server::Server(int port, int poolSize)
    : port(port), threadPool(poolSize) {}

void Server::start() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 10);

    std::cout << "[INFO] Server started on port " << port << std::endl;

    acceptConnections();
}

void Server::acceptConnections() {
    while (true) {
        sockaddr_in client_address{};
        socklen_t client_len = sizeof(client_address);
        int client_socket = accept(server_fd, (struct sockaddr*)&client_address, &client_len);

        threadPool.enqueue([client_socket]() {
            RequestHandler::handleRequest(client_socket);
        });
    }
}

