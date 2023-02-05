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

                if (listener.accept(*newClient->getSocket()) == sf::Socket::Done) {
                    clients.push_back(newClient);
                    selector.add(*newClient->getSocket());
                    std::cout << "New client connected: " << newClient->id << std::endl;
                } else {
                    std::cout << "Failed to accept new client" << std::endl;
                    delete newClient;
                }
            } else {
                auto it = clients.begin();

                while (it != clients.end()) {
                    auto client = *it;
                    auto tcpSocket = client->getSocket();

                    if (selector.isReady(*tcpSocket)) {
                        sf::Packet packet;

                        std::cout << "Waiting for packet from client " << client->id << std::endl;
                        if (tcpSocket->receive(packet) == sf::Socket::Done) {
                            handleTcpCommand(packet, client);
                        } else {
                            selector.remove(*tcpSocket);
                            std::cout << "Client " << client->id << " disconnected" << std::endl;
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
    for (auto game : games) {
        delete game;
    }
}
