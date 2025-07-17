#include "Server.h"

int main() {
  //  std::string staticFolder = (argc > 1) ? argv[1] : "static/";
    Server server(8080, 8);  // Port 8080, 8 worker threads
    server.start();
    return 0;
}
