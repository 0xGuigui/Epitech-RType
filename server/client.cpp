#include "server/server.h"

Client::Client() {
    this->_id = Server::nextClientId;
    if (Server::nextClientId == INT_MAX) {
        Server::nextClientId = 0;
    }
    Server::nextClientId++;
    this->_tcpSocket = std::make_unique<sf::TcpSocket>();
    this->_udpSocket = std::make_unique<sf::UdpSocket>();
    this->_tcpSocket->setBlocking(false);
    this->_udpSocket->setBlocking(false);
}

ClientSockets Client::getSockets() {
    return std::make_tuple(this->_tcpSocket.get(), this->_udpSocket.get());
}

int Client::getId() const {
    return _id;
}

void Client::sendTcpPacket(sf::Packet &packet) {
    this->_tcpSocket->send(packet);
}

void Client::setName(const std::string &name) {
    _name = name;
}

const std::string &Client::getName() const {
    return _name;
}

void Client::setGame(Game *game) {
    _game = game;
}

Game *Client::getGame() const {
    return _game;
}
