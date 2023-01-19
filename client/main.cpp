#include "SFML/Graphics.hpp"
#include "client/rtype.h"

// init global instance of RType
RType rtype("resources");

int main() {
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    UiSystem uiSystem;

    sf::RectangleShape shape({100.f, 100.f});
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({50.f, 50.f});

    auto test = StatelessUiComponent<sf::RectangleShape>(shape);

    uiSystem.addLayer({&test}, false);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            rtype.keyboard.update(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        uiSystem.draw(window);
        window.display();
    }
}
