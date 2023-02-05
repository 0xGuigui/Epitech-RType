#pragma once

#include <SFML/Network.hpp>
#include <vector>
#include "enums.h"

struct PlayerInfo {
    sf::Uint32 id;
    std::string name;
    sf::IpAddress ip;
};

struct GameInfo {
    std::string name;
    GameStatus status;
    std::vector<PlayerInfo> players;
    PlayerInfo host;
};
