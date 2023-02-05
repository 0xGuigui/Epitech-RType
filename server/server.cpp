#include "server/server.h"

int Server::nextClientId = 0;

Server::Server(int port) {
    int status = listener.listen(port);

    if (status != sf::Socket::Done) {
        throw std::runtime_error("Failed to listen on port " + std::to_string(port));
    }
    std::cout << "Listening on port " << port << std::endl;
    std::cout << "Current server address is: " << sf::IpAddress::getLocalAddress() << ":" << port << std::endl;
    selector.add(listener);
    running = true;
}

void Server::run() {
    while (running) {
        if (selector.wait()) {
            if (selector.isReady(listener)) {
                auto newClient = new Client();
                auto sockets = newClient->getSockets();

                if (listener.accept(*std::get<0>(sockets)) == sf::Socket::Done) {
                    clients.push_back(newClient);
                    selector.add(*std::get<0>(sockets));
                    std::cout << "New client connected: " << newClient->getId() << std::endl;
                } else {
                    std::cout << "Failed to accept new client" << std::endl;
                    delete newClient;
                }
            } else {
                auto it = clients.begin();

                while (it != clients.end()) {
                    auto client = *it;
                    auto sockets = client->getSockets();

                    if (selector.isReady(*std::get<0>(sockets))) {
                        sf::Packet packet;

                        std::cout << "Waiting for packet from client " << client->getId() << std::endl;
                        if (std::get<0>(sockets)->receive(packet) == sf::Socket::Done) {
                            handleTcpCommand(packet, client);
                        } else {
                            selector.remove(*std::get<0>(sockets));
                            std::cout << "Client " << client->getId() << " disconnected" << std::endl;
                            delete client;
                            it = clients.erase(it);
                            continue;
                        }
                    }
                    ++it;
                }
            }
        }
    }
}

void Server::stop() {
    running = false;
}

Server::~Server() {
    std::cout << "Stopping server" << std::endl;
    listener.close();

    for (auto client : clients) {
        delete client;
    }
}
