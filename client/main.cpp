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

    // green box that turn red when clicked
    auto test = StatefulUiComponent<sf::RectangleShape>(shape, [&shape]() {
        sf::Color currentColor = shape.getFillColor();

        if (currentColor == sf::Color::Red)
            shape.setFillColor(sf::Color::Green);
        else
            shape.setFillColor(sf::Color::Red);
    });

    uiSystem.addLayer({&test}, false);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // handle user controls
            rtype.keyboard.update(event);
            // handle ui events such as click or hover
            uiSystem.dispatchEvent(event);
        }
        window.clear();
        uiSystem.draw(window);
        window.display();
    }
}
