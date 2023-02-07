#include "server/server.h"

Game::Game(Client *host, const std::string &name) {
    this->host = host;
    auto newClient = GameClient();
    newClient.client = host;
    this->clients.push_back(newClient);
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
    auto newClient = GameClient();
    newClient.client = client;
    this->clients.push_back(newClient);
    client->game = this;
    return std::nullopt;
}

optError Game::removeClient(Client *client) {
    // @TODO if the player leaving is the host, notify all player that they also leave the game
    // first case is not supposed to happen
    if (client == nullptr || client->game == nullptr) {
        return {"Client is not in a game"};
    }
    auto it = std::find_if(
            this->clients.begin(),
            this->clients.end(),
            [client](const GameClient &gameClient) {
                return gameClient.client == client;
            }
    );
    if (it == this->clients.end()) {
        return {"Client is not in this game"};
    } else {
        client->game = nullptr;
        this->clients.erase(it);
    }
    return std::nullopt;
}

const std::string &Game::getName() const {
    return this->name;
}

GameInfo Game::getInfo() const {
    GameInfo info;
    std::vector<PlayerInfo> players(this->clients.size());

    info.name = this->name;
    info.status = this->status;
    info.players = players;
    for (int i = 0; i < this->clients.size(); i++) {
        info.players[i].name = this->clients[i].client->name;
        info.players[i].id = this->clients[i].client->id;
        info.players[i].ip = this->clients[i].client->getSocket()->getRemoteAddress();
    }
    return info;
}

void Game::computeGameTick(sf::Int32 elapsed) {
    // @TODO compute game tick
}

void Game::sendGameTick() {
    for (auto client: this->clients) {
        sf::Packet packet;

        packet << RES_GAME_TICK;
        this->udpSocket->send(packet, client.ip, client.port);
    }
}

void Game::readClientPackets() {
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;

    while (this->udpSocket->receive(packet, sender, port) == sf::Socket::Done) {
        for (auto client: this->clients) {
            if (client.client->getSocket()->getRemoteAddress() == sender) {
                if (client.port == 0) {
                    client.port = port;
                    client.ip = sender;
                }
                this->handleUdpPacket(packet, client.client);
                break;
            }
        }
    }
}

void Game::start(Server *server) {
    this->status = GAME_STARTED;
    this->udpSocket = new sf::UdpSocket();
    this->udpSocket->bind(sf::Socket::AnyPort);
    for (auto &_client: this->clients) {
        _client.client->sendTcpData(RES_GAME_STARTED, this->udpSocket->getLocalPort());
    }

    this->gameThread = new std::thread([this, server]() {
        sf::Clock clock;
        sf::Int32 lastTick = 0;

        while (this->status == GAME_STARTED) {
            sf::Int32 elapsed = clock.getElapsedTime().asMilliseconds();

            if (elapsed - lastTick >= SERVER_TICK_TIME) {
                lastTick = elapsed;
                this->computeGameTick(elapsed);
                this->sendGameTick();
            }
            this->readClientPackets();
        }
    });
}

Game::~Game() {
    if (this->gameThread != nullptr) {
        this->gameThread->join();
        delete this->gameThread;
    }
    for (auto client: this->clients) {
        client.client->game = nullptr;
    }
    udpSocket->unbind();
    delete udpSocket;
}
