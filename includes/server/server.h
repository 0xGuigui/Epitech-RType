#pragma once

#include <SFML/Network.hpp>
#include <memory>
#include <iostream>
#include <tuple>
#include <climits>
#include <optional>
#include <atomic>
#include <thread>
#include "lib/packet.h"
#include "lib/structs.h"

#define MAX_GAME_PLAYERS 4

typedef std::optional<const char *> optError;

// Forward declaration of the Game class
class Game;
class Server;

class Client {
public:
    int id;
    std::string name;
    std::unique_ptr<sf::TcpSocket> tcpSocket;
    Game *game = nullptr;

public:
    Client();

    sf::TcpSocket *getSocket();

    void sendTcpPacket(sf::Packet &packet) const;

    template<typename... Args>
    void sendTcpData(TcpResponse response, Args... args) {
        sf::Packet packet;

        packet << response;
        (packet << ... << args);
        tcpSocket->send(packet);
    }
};

class Game {
public:
    std::vector<Client *> clients;
    Client *host;
    std::atomic<GameStatus> status = GAME_WAITING;
    sf::UdpSocket *udpSocket = nullptr;
    std::string name;

public:
    Game(Client *host, const std::string &name);

    ~Game();

    const std::string &getName() const;

    optError addClient(Client *client);

    optError removeClient(Client *client);

    GameInfo getInfo() const;

    void start(Server *server);
};

class Server {
public:
    sf::TcpListener listener;
    std::vector<Client *> clients;
    std::vector<Game *> games;
    sf::SocketSelector selector;
    bool running = false;
    std::vector<std::thread> gameThreads;

public:
    explicit Server(int port = 5000);

    ~Server();

    void run();

    void stop();

    void handleTcpCommand(sf::Packet &packet, Client *client);

    // used to generate ids for clients
    static int nextClientId;
};
