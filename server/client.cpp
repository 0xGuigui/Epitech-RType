#include "server/server.h"

Client::Client() {
    this->_id = Server::nextClientId;
    if (Server::nextClientId == INT_MAX) {
        Server::nextClientId = 0;
    }
    Server::nextClientId++;
    this->_tcpSocket = std::make_unique<sf::TcpSocket>();
    this->_tcpSocket->setBlocking(false);
}

sf::TcpSocket *Client::getSocket() {
    return this->_tcpSocket.get();
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
