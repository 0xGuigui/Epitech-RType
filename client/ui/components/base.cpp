#include "client/ui/core.h"

template<typename T>
T &UiComponent<T>::getSFMLElement() const {
    return SFMLElement;
}

template<typename T>
void UiComponent<T>::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(SFMLElement, states);
}

template<typename T>
bool StatelessUiComponent<T>::handleEvent(sf::Event &event) {
    return false;
}

template<typename T>
bool StatefulUiComponent<T>::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (this->getSFMLElement().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            onClick();
            return true;
        }
    }
    return false;
}
