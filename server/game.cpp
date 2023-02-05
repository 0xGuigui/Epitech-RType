#include "server/server.h"

Game::Game(Client *host, const std::string &name) {
    this->host = host;
    this->clients.push_back(host);
    this->name = name;
    host->game = this;
}

optError Game::addClient(Client *client) {
    if (this->clients.size() >= MAX_GAME_PLAYERS) {
        return {"Game is full"};
    } else if (this->status != GAME_WAITING) {
        return {"Game is already started"};
    } else if (client->game != nullptr) {
        return {"Client is already in a game"};
    }
    this->clients.push_back(client);
    client->game = this;
    return std::nullopt;
}

optError Game::removeClient(Client *client) {
    // @TODO if the player leaving is the host, notify all player that they also leave the game
    // first case is not supposed to happen
    if (client == nullptr || client->game == nullptr) {
        return {"Client is not in a game"};
    }
    auto it = this->clients.erase(
            std::remove(this->clients.begin(), this->clients.end(), client),
            this->clients.end()
    );
    if (it == this->clients.end()) {
        return {"Client is not in this game"};
    } else {
        client->game = nullptr;
    }
    return std::nullopt;
}

const std::string &Game::getName() const {
    return this->name;
}

Game::~Game() {
    for (auto client : this->clients) {
        client->game = nullptr;
    }
    udpSocket.unbind();
}

GameInfo Game::getInfo() const {
    GameInfo info;
    std::vector<PlayerInfo> players(this->clients.size());

    info.name = this->name;
    info.status = this->status;
    info.players = players;
    for (int i = 0; i < this->clients.size(); i++) {
        info.players[i].name = this->clients[i]->name;
        info.players[i].id = this->clients[i]->id;
        info.players[i].ip = this->clients[i]->getSocket()->getRemoteAddress();
    }
    return info;
}
