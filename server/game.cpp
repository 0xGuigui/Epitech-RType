#include "server/server.h"

Game::Game(Client *host, const std::string &name) {
    this->_host = host;
    this->_clients.push_back(host);
    this->_name = name;
    host->setGame(this);
}

optError Game::addClient(Client *client) {
    if (this->_clients.size() >= MAX_GAME_PLAYERS) {
        return {"Game is full"};
    } else if (this->_status != GAME_WAITING) {
        return {"Game is already started"};
    } else if (client->getGame() != nullptr) {
        return {"Client is already in a game"};
    }
    this->_clients.push_back(client);
    client->setGame(this);
    return std::nullopt;
}

optError Game::removeClient(Client *client) {
    // @TODO if the player leaving is the host, notify all player that they also leave the game
    // first case is not supposed to happen
    if (client == nullptr || client->getGame() == nullptr) {
        return {"Client is not in a game"};
    }
    auto it = this->_clients.erase(
            std::remove(this->_clients.begin(), this->_clients.end(), client),
            this->_clients.end()
    );
    if (it == this->_clients.end()) {
        return {"Client is not in this game"};
    } else {
        client->setGame(nullptr);
    }
    return std::nullopt;
}

const std::string &Game::getName() const {
    return this->_name;
}

Game::~Game() {
    for (auto client : this->_clients) {
        client->setGame(nullptr);
    }
    _udpSocket.unbind();
}

GameInfo Game::getInfo() const {
    GameInfo info;
    std::vector<PlayerInfo> players(this->_clients.size());

    info.name = this->_name;
    info.status = this->_status;
    info.players = players;
    for (int i = 0; i < this->_clients.size(); i++) {
        info.players[i].name = this->_clients[i]->getName();
        info.players[i].id = this->_clients[i]->getId();
        info.players[i].ip = this->_clients[i]->getSocket()->getRemoteAddress();
    }
    return info;
}
