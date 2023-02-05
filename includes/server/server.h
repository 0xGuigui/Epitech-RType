#pragma once

#include <SFML/Network.hpp>
#include <memory>
#include <iostream>
#include <tuple>
#include <climits>
#include <optional>
#include "lib/packet.h"
#include "lib/structs.h"

#define MAX_GAME_PLAYERS 4

typedef std::optional<const char *> optError;

// Forward declaration of the Game class
class Game;

class Client {
private:
    int _id;
    std::string _name;
    std::unique_ptr<sf::TcpSocket> _tcpSocket;
    Game *_game = nullptr;
    sf::IpAddress _ip;

public:
    Client();

    sf::TcpSocket *getSocket();

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
    Client *_host;
    GameStatus _status = GAME_WAITING;
    sf::UdpSocket _udpSocket;
    std::string _name;

public:
    Game(Client *host, const std::string &name);

    ~Game();

    const std::string &getName() const;

    optError addClient(Client *client);

    optError removeClient(Client *client);

    GameInfo getInfo() const;
};

class Server {
public:
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
