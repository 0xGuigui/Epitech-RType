#include "client/ui/components.h"

void StatefulUiComponent::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            _onClick();
        }
    }
}
