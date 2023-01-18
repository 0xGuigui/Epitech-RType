#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class UiComponent {
protected:
    sf::Drawable &_drawable;

public:
    explicit UiComponent(sf::Drawable &drawable) : _drawable(drawable) {}

    sf::Drawable &getDrawable() const {
        return _drawable;
    }

    virtual void draw(sf::RenderWindow &window) {
        window.draw(_drawable);
    }

    virtual void handleEvent(sf::Event &event) = 0;
};

class StatelessUiComponent : public UiComponent {
public:
    explicit StatelessUiComponent(sf::Drawable &drawable) : UiComponent(drawable) {}

    void handleEvent(sf::Event &event) override {};
};

class StatefulUiComponent : public UiComponent {
private:
    std::function<void()> _onClick;

public:
    explicit StatefulUiComponent(sf::Drawable &drawable, const std::function<void()> &_onClick) :
            UiComponent(drawable),
            _onClick(_onClick) {}

    void handleEvent(sf::Event &event) override;
};


// quick example
class UiText : public StatelessUiComponent {
public:
    UiText();
};
