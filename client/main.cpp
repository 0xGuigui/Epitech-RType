#include "SFML/Graphics.hpp"
#include "client/rtype.h"
#include "client/entities/player.h"

// Clion run version
//RType rtype("../resources");
// Terminal run version
// init global instance of RType
RType rtype("resources");

#include "client/components/render_component.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML works!");

//    std::shared_ptr<Player> player = rtype.world.createEntity<Player>();
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
