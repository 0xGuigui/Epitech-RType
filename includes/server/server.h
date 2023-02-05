#pragma once

#include <SFML/Network.hpp>
#include <memory>
#include <iostream>
#include <tuple>
#include <climits>

typedef std::tuple<sf::TcpSocket *, sf::UdpSocket *> ClientSockets;

class Client {
private:
    int _id;
    std::unique_ptr<sf::TcpSocket> _tcpSocket;
    std::unique_ptr<sf::UdpSocket> _udpSocket;

public:
    Client();

    ClientSockets getSockets();

    [[nodiscard]] int getId() const;
};

class Server {
private:
    sf::TcpListener listener;
    std::vector<Client *> clients;
    sf::SocketSelector selector;
    bool running = false;

public:
    explicit Server(int port = 5000);

    ~Server();

    void run();

    void stop();

    // used to generate ids for clients
    static int nextClientId;
};
