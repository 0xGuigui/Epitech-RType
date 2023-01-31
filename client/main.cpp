#include "SFML/Graphics.hpp"
#include "client/rtype.h"

// init global instance of RType
RType rtype("resources");

int main() {
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");

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
