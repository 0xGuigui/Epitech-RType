#include "server/server.h"

Client::Client() {
    this->id = Server::nextClientId;
    if (Server::nextClientId == INT_MAX) {
        Server::nextClientId = 0;
    }
    Server::nextClientId++;
    this->tcpSocket = std::make_unique<sf::TcpSocket>();
    this->tcpSocket->setBlocking(false);
}

sf::TcpSocket *Client::getSocket() const {
    return this->tcpSocket.get();
}

void Client::sendTcpPacket(sf::Packet &packet) const {
    this->tcpSocket->send(packet);
}

std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << "Client " << client.id;

    if (client.name.empty()) {
        os << " (no name)";
    } else {
        os << " (" << client.name << ")";
    }
    return os;
}
