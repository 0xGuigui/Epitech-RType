#include "server/server.h"

void Game::handleUdpPacket(sf::Packet &packet, Client *client) {
    std::cout << "Received packet from" << client->id << std::endl;
}
