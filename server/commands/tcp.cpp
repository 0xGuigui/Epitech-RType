#include "server/server.h"

void setName(sf::Packet &packet, Client *client) {
    std::string name;

    packet >> name;
    client->name = name;

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
    client->game = game;
    server->games.push_back(game);
    sf::Packet response = createResponse(RES_OK, "Game created");
    client->sendTcpPacket(response);
}

void listGames(Server *server, Client *client) {
    sf::Packet response;

    response << RES_LIST_GAMES << server->games;
    client->sendTcpPacket(response);
}

void joinGame(Server *server, sf::Packet &packet, Client *client) {
    std::string name;

    packet >> name;
    if (client->game != nullptr) {
        sf::Packet response = createResponse(RES_ERROR, "You are already in a game");
        client->sendTcpPacket(response);
        return;
    }
    for (auto &game: server->games) {
        if (game->getName() == name) {
            if (game->clients.size() >= MAX_GAME_PLAYERS) {
                sf::Packet response = createResponse(RES_ERROR, "Game is full");
                client->sendTcpPacket(response);
                return;
            }
            if (game->status != GAME_WAITING) {
                sf::Packet response = createResponse(RES_ERROR, "Game can't be joined");
                client->sendTcpPacket(response);
                return;
            }
            game->addClient(client);
            client->game = game;
            sf::Packet response = createResponse(RES_OK, "Joined game");
            client->sendTcpPacket(response);
            return;
        }
    }
    sf::Packet response = createResponse(RES_ERROR, "Game not found");
    client->sendTcpPacket(response);
}

void leaveGame(Server *server, Client *client) {
    Game *game = client->game;

    // @TODO: normalize this process as this need to be done when a player disconnect
    if (game == nullptr)
        return client->sendTcpData(RES_ERROR, "You are not in a game");
    if (game->host == client) {
        for (auto &_client: game->clients) {
            _client.client->game = nullptr;
            if (_client.client != client) {
                _client.client->sendTcpData(RES_USER_KICKED, "Game closed");
            }
        }
        server->games.erase(std::find(server->games.begin(), server->games.end(), game));
        delete game;
    } else {
        game->removeClient(client);
    }
    client->game = nullptr;
    sf::Packet response = createResponse(RES_OK, "Left game");
    client->sendTcpPacket(response);
    client->sendTcpData(RES_OK, "You left the game");
}

void disconnectClient(Server *server, Client *client) {
    Game *game = client->game;

    if (game != nullptr) {
        if (game->host == client) {
            for (auto &_client: game->clients) {
                _client.client->game = nullptr;
                if (_client.client != client) {
                    _client.client->sendTcpData(RES_USER_KICKED, "Game closed");
                }
            }
            server->games.erase(std::find(server->games.begin(), server->games.end(), game));
            delete game;
        } else {
            game->removeClient(client);
        }
    }
    server->clients.erase(std::find(server->clients.begin(), server->clients.end(), client));
    client->getSocket()->disconnect();
    delete client;
}

void startGame(Server *server, Client *client) {
    Game *game = client->game;

    if (game == nullptr)
        return client->sendTcpData(RES_ERROR, "You are not in a game");
    if (game->host != client)
        return client->sendTcpData(RES_ERROR, "You are not the host");
    if (game->status != GAME_WAITING)
        return client->sendTcpData(RES_ERROR, "Game already started");
    game->start(server);
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
            listGames(this, client);
            break;
        case REQ_JOIN_GAME:
            joinGame(this, packet, client);
            break;
        case REQ_LEAVE_GAME:
            leaveGame(this, client);
        case REQ_DISCONNECT:
            disconnectClient(this, client);
        case REQ_START_GAME:
            startGame(this, client);
        default:
            break;
    }
}
