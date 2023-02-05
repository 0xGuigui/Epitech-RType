#pragma once

#include <SFML/Network.hpp>
#include <string>
#include "structs.h"
#include "enums.h"

sf::Packet &operator<<(sf::Packet &packet, const TcpRequest &request);

sf::Packet &operator>>(sf::Packet &packet, TcpRequest &request);

sf::Packet &operator<<(sf::Packet &packet, const TcpResponse &response);

sf::Packet &operator>>(sf::Packet &packet, TcpResponse &response);

sf::Packet &operator<<(sf::Packet &packet, const GameStatus &status);

sf::Packet &operator>>(sf::Packet &packet, GameStatus &status);

sf::Packet &operator<<(sf::Packet &packet, const PlayerInfo &player);

sf::Packet &operator>>(sf::Packet &packet, PlayerInfo &player);

sf::Packet &operator<<(sf::Packet &packet, const GameInfo &game);

sf::Packet &operator>>(sf::Packet &packet, GameInfo &game);

sf::Packet createResponse(TcpResponse response, const std::string &message);
