#include "server/server.h"

void setName(sf::Packet &packet, Client *client) {
    std::string name;

    packet >> name;
    client->setName(name);

    sf::Packet response = createResponse(RES_OK, "Name set");
    client->sendTcpPacket(response);
}

void createGame(Server *server, sf::Packet &packet, Client *client) {
    std::string name;

    packet >> name;
    for (auto &game: server->games) {
        if (game->getName() == name) {
            sf::Packet response = createResponse(RES_ERROR, "Name already taken");
            client->sendTcpPacket(response);
            return;
        }
    }
    Game *game = new Game(client, name);
    client->setGame(game);
    server->games.push_back(game);
    sf::Packet response = createResponse(RES_OK, "Game created");
    client->sendTcpPacket(response);
}

void listGames(Server *server, sf::Packet &packet, Client *client) {
    sf::Packet response;
    sf::Uint32 size = server->games.size();

    response << RES_LIST_GAMES << size;
    for (auto &game: server->games) {
        response << game->getInfo();
    }
    client->sendTcpPacket(response);
}

void Server::handleTcpCommand(sf::Packet &packet, Client *client) {
    TcpRequest request;

    packet >> request;
    switch (request) {
        case REQ_SET_NAME:
            setName(packet, client);
            break;
        case REQ_CREATE_GAME:
            createGame(this, packet, client);
            break;
        case REQ_LIST_GAMES:
            listGames(this, packet, client);
            break;
        default:
            break;
    }
}
