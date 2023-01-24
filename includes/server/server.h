#pragma once

#include <SFML/Network.hpp>
#include <memory>
#include <iostream>
#include <tuple>
#include <climits>

typedef std::tuple<sf::TcpSocket *, sf::UdpSocket *> ClientSockets;

class Client {
private:
    int id;
    std::unique_ptr<sf::TcpSocket> tcpSocket;
    std::unique_ptr<sf::UdpSocket> udpSocket;

public:
    Client();

    ClientSockets getSockets() const;
};

class Server {
private:
    bool running = false;

public:
    explicit Server(int port = 5000);

    void run();

    static int nextClientId;
};
