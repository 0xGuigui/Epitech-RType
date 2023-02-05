#pragma once

#include <SFML/Network.hpp>
#include <string>
#include "enums.h"

sf::Packet &operator<<(sf::Packet &packet, const TcpRequest &request);

sf::Packet &operator>>(sf::Packet &packet, TcpRequest &request);

sf::Packet &operator<<(sf::Packet &packet, const TcpResponse &response);

sf::Packet &operator>>(sf::Packet &packet, TcpResponse &response);

sf::Packet createResponse(TcpResponse response, const std::string &message);
