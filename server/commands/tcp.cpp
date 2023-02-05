#include "server/server.h"

void setName(sf::Packet &packet, Client *client) {
    std::string name;

    packet >> name;
    client->setName(name);

    sf::Packet response = createResponse(RES_OK, "Name set");
    client->sendTcpPacket(response);
}

void createGame(sf::Packet &packet, Client *client) {
    std::string name;

    packet >> name;
}

void Server::handleTcpCommand(sf::Packet &packet, Client *client) {
    TcpRequest request;

    packet >> request;
    switch (request) {
        case REQ_SET_NAME:
            setName(packet, client);
            break;
        default:
            break;
    }
}
