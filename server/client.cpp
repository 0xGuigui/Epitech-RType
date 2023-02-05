#include "server/server.h"

Client::Client() {
    this->_id = Server::nextClientId;
    if (Server::nextClientId == INT_MAX) {
        Server::nextClientId = 0;
    }
    Server::nextClientId++;
    this->_tcpSocket = std::make_unique<sf::TcpSocket>();
    this->_udpSocket = std::make_unique<sf::UdpSocket>();
}

ClientSockets Client::getSockets() {
    return std::make_tuple(this->_tcpSocket.get(), this->_udpSocket.get());
}

int Client::getId() const {
    return _id;
}
