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
#define SERVER_TICK_RATE 20
#define SERVER_TICK_TIME (1000 / SERVER_TICK_RATE)

typedef std::optional<const char *> optError;

// Forward declaration
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

    [[nodiscard]] sf::TcpSocket *getSocket() const;

    void sendTcpPacket(sf::Packet &packet) const;

    template<typename... Args>
    void sendTcpData(TcpResponse response, Args... args) {
        sf::Packet packet;

        packet << response;
        (packet << ... << args);
        tcpSocket->send(packet);
    }
};

std::ostream& operator<<(std::ostream& os, const Client& client);

struct GameClient {
    Client *client = nullptr;
    sf::IpAddress ip = sf::IpAddress::None;
    unsigned short port = 0;
};

class Game {
public:
    std::vector<GameClient> clients;
    Client *host;
    sf::UdpSocket *udpSocket = nullptr;
    std::thread *gameThread = nullptr;
    std::string name;
    std::atomic<GameStatus> status = GAME_WAITING;

public:
    Game(Client *host, const std::string &name);

    ~Game();

    [[nodiscard]] const std::string &getName() const;

    optError addClient(Client *client);

    optError removeClient(Client *client);

    [[nodiscard]] GameInfo getInfo() const;

    void readClientPackets();

    void handleUdpPacket(sf::Packet &packet, Client *client);

    void start(Server *server);

    void computeGameTick(sf::Int32 elapsed);

    void sendGameTick();
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
