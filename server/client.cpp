#include "server/server.h"

Client::Client() {
    this->id = Server::nextClientId;
    if (Server::nextClientId == INT_MAX) {
        Server::nextClientId = 0;
    }
    Server::nextClientId++;
    this->tcpSocket = std::make_unique<sf::TcpSocket>();
    this->udpSocket = std::make_unique<sf::UdpSocket>();
}

ClientSockets Client::getSockets() const {
    return std::make_tuple(this->tcpSocket.get(), this->udpSocket.get());
}
