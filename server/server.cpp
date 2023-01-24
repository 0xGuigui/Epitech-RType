#include "server/server.h"

Server::Server(int port) {
    std::cout << port << std::endl;
}

void Server::run() {

    while (running) {
        std::cout << "test" << std::endl;
    }
}
