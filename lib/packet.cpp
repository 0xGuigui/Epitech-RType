#include "lib/packet.h"

sf::Packet &operator<<(sf::Packet &packet, const TcpRequest &request) {
    return packet << static_cast<sf::Uint8>(request);
}

sf::Packet &operator>>(sf::Packet &packet, TcpRequest &request) {
    sf::Uint8 requestValue;

    if (packet >> requestValue)
        request = static_cast<TcpRequest>(requestValue);
    return packet;
}

sf::Packet &operator<<(sf::Packet &packet, const TcpResponse &response) {
    return packet << static_cast<sf::Uint8>(response);
}

sf::Packet &operator>>(sf::Packet &packet, TcpResponse &response) {
    sf::Uint8 responseValue;

    if (packet >> responseValue)
        response = static_cast<TcpResponse>(responseValue);
    return packet;
}

sf::Packet createResponse(TcpResponse response, const std::string &message) {
    sf::Packet packet;

    packet << response;
    packet << message;
    return packet;
}

sf::Packet &operator<<(sf::Packet &packet, const GameStatus &status) {
    return packet << static_cast<sf::Uint8>(status);
}

sf::Packet &operator>>(sf::Packet &packet, GameStatus &status) {
    sf::Uint8 statusValue;

    if (packet >> statusValue)
        status = static_cast<GameStatus>(statusValue);
    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const PlayerInfo& playerInfo) {
    return packet << playerInfo.id << playerInfo.name << playerInfo.ip.toString();
}

sf::Packet& operator >> (sf::Packet& packet, PlayerInfo& playerInfo) {
    std::string ipAddress;

    packet >> playerInfo.id >> playerInfo.name >> ipAddress;
    playerInfo.ip = ipAddress;
    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const GameInfo& gameInfo) {
    packet << gameInfo.name << gameInfo.status << gameInfo.players;
    return packet;
}

sf::Packet& operator >> (sf::Packet& packet, GameInfo& gameInfo) {
    packet >> gameInfo.name >> gameInfo.status >> gameInfo.players;
    return packet;
}
