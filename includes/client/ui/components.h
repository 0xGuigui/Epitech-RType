#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <utility>

class IUiComponent {
public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

    virtual ~IUiComponent() = default;
};

template <typename T>
class UiComponent : public IUiComponent, public sf::Drawable, public sf::Transformable {
protected:
    T &SFMLElement;

public:
    explicit UiComponent(T &SFMLElement) : SFMLElement(SFMLElement) {}

    T &getSFMLElement() const {
        return SFMLElement;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        target.draw(SFMLElement, states);
    }

    virtual void handleEvent(sf::Event &event) = 0;
};

template <typename T>
class StatelessUiComponent : public UiComponent<T> {
public:
    explicit StatelessUiComponent(T &SFMLElement) : UiComponent<T>(SFMLElement) {}

    void handleEvent(sf::Event &event) override {}
};

template <typename T>
class StatefulUiComponent : public UiComponent<T> {
public:
    explicit StatefulUiComponent(T &SFMLElement, std::function<void()> onClick) : UiComponent<T>(SFMLElement), onClick(std::move(onClick)) {}

    void handleEvent(sf::Event &event) override {
        if (event.type == sf::Event::MouseButtonPressed && this->SFMLElement.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            onClick();
        }
    }

private:
    std::function<void()> onClick;
};
