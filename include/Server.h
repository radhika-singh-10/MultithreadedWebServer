


#pragma once

#include "ThreadPool.h"

class Server {
public:
    Server(int port, int poolSize);
    void start();

private:
    int server_fd;
    int port;
    ThreadPool threadPool;

    void acceptConnections();
};

