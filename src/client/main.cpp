//
// Created by Paul Gervais on 09/01/2023.
//

#include <iostream>
#include "lib/lib.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    helloWorld();
    std::cout << "Hello from client" << std::endl;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.display();
    }
}
