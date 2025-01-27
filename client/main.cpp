#include "SFML/Graphics.hpp"
#include "client/rtype.h"
#include "client/entities/entities.h"
#include "client/components/components.h"
#include "client/entities/powerup.h"
#include "client/utils/background.h"
#include "lib/random.h"
#include "SFML/Network.hpp"
#include "lib/packet.h"

// Clion run version
//RType rtype("../resources");
// Terminal run version
// init global instance of RType
RType rtype("resources");

int main() {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("localhost", 50000);

    if (status != sf::Socket::Done) {
        std::cerr << "Error while connecting to server" << std::endl;
        return 1;
    }
    TcpResponse response;
    sf::Packet packet;
    packet << REQ_SET_NAME << "test";
    socket.send(packet);
    packet.clear();
    socket.receive(packet);
    packet >> response;
    packet.clear();
    packet << REQ_CREATE_GAME << "test game";
    socket.send(packet);
    packet.clear();
    socket.receive(packet);
    packet.clear();
    packet << REQ_LIST_GAMES;
    socket.send(packet);
    packet.clear();
    socket.receive(packet);
    packet >> response;

    if (response == RES_LIST_GAMES) {
        std::vector<GameInfo> games;

        packet >> games;
        for (auto &game : games) {
            std::cout << game.name << std::endl;
        }
    }

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "R-Type");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    std::shared_ptr<Background> background = rtype.world.createEntity<Background>(window);
    std::shared_ptr<Background> background2 = rtype.world.createEntity<Background>(window);
    background2->getComponent<PositionComponent>()->setPosition(static_cast<float>(window.getSize().x), 0);
    createMainPlayer();
    std::shared_ptr<Monster> monster = rtype.world.createEntity<Monster>();
    monster->getComponent<VelocityComponent>()->setVelocity(-80, 0);
    monster->getComponent<PositionComponent>()->setPosition(static_cast<float>(window.getSize().x), static_cast<float>(Random::generate() % 500) + 300);
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            rtype.keyboard.update(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        rtype.world.update(window);
        window.display();
    }
}
