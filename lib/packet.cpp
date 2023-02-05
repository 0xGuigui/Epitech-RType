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
