#pragma once

#include <SFML/Network.hpp>
#include <memory>
#include <iostream>
#include <tuple>
#include <climits>
#include <optional>
#include "lib/packet.h"

#define MAX_GAME_PLAYERS 4

typedef std::tuple<sf::TcpSocket *, sf::UdpSocket *> ClientSockets;

// Forward declaration of the Game class
class Game;

class Client {
private:
    int _id;
    std::string _name;
    std::unique_ptr<sf::TcpSocket> _tcpSocket;
    std::unique_ptr<sf::UdpSocket> _udpSocket;
    Game *_game = nullptr;

public:
    Client();

    ClientSockets getSockets();

    void sendTcpPacket(sf::Packet &packet);

    void setName(const std::string &name);

    void setGame(Game *game);

    Game *getGame() const;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] int getId() const;
};

class Game {
private:
    std::vector<Client *> _clients;
    Client *host;
    GameStatus _status = GAME_WAITING;

public:
    Game() = default;

    std::optional<const char *> addClient(Client *client);
};

class Server {
private:
    sf::TcpListener listener;
    std::vector<Client *> clients;
    std::vector<Game *> games;
    sf::SocketSelector selector;
    bool running = false;

public:
    explicit Server(int port = 5000);

    ~Server();

    void run();

    void stop();

    void handleTcpCommand(sf::Packet &packet, Client *client);

    // used to generate ids for clients
    static int nextClientId;
};
