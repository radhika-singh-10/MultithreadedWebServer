#include "RequestHandler.h"
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <fstream>

void RequestHandler::handleRequest(int client_socket) {
    char buffer[4096] = {0};
    read(client_socket, buffer, sizeof(buffer) - 1);

    std::string request(buffer);
    std::cout << "[REQUEST]\n" << request << std::endl;

    std::string response;

    if (request.find("GET /") != std::string::npos) {
        std::ifstream file("static/index.html");

        if (file) {
            std::string body((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());

            response = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: text/html\r\n"
                       "Content-Length: " + std::to_string(body.length()) + "\r\n"
                       "\r\n" + body;
        } else {
            std::string body = "<html><body><h1>500 Internal Server Error</h1></body></html>";
            response = "HTTP/1.1 500 Internal Server Error\r\n"
                       "Content-Type: text/html\r\n"
                       "Content-Length: " + std::to_string(body.length()) + "\r\n"
                       "\r\n" + body;
        }

    }
    else if (request.find("POST /submit") != std::string::npos) {
        size_t body_pos = request.find("\r\n\r\n");
        std::string post_body = "";
        if (body_pos != std::string::npos) {
            post_body = request.substr(body_pos + 4);
            std::cout << "[POST DATA]\n" << post_body << std::endl;
        }

        std::string body = "<html><body><h1>POST Received!</h1><p>" + post_body + "</p></body></html>";

        response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html\r\n"
                   "Content-Length: " + std::to_string(body.length()) + "\r\n"
                   "\r\n" + body;
    }
    else {
        std::string body = "<html><body><h1>404 Not Found</h1></body></html>";
        response = "HTTP/1.1 404 Not Found\r\n"
                   "Content-Type: text/html\r\n"
                   "Content-Length: " + std::to_string(body.length()) + "\r\n"
                   "\r\n" + body;
    }

    send(client_socket, response.c_str(), response.length(), 0);
    close(client_socket);
}


