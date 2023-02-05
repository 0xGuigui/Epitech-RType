#include "server/server.h"

std::optional<const char *> Game::addClient(Client *client) {
    if (this->_clients.size() >= MAX_GAME_PLAYERS) {
        return std::make_optional<const char *>("Game is full");
    } else if (this->_status != GAME_WAITING) {
        return std::make_optional<const char *>("Game is already started");
    } else if (client->getGame() != nullptr) {
        return std::make_optional<const char *>("Client is already in a game");
    }
    this->_clients.push_back(client);
    client->setGame(this);
    return std::nullopt;
}
