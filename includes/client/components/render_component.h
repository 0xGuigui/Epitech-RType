#include "component.h"
#include "SFML/Graphics.hpp"

class RenderComponent : public Component {
private:
    sf::Sprite _render;
public:
    explicit RenderComponent(const sf::Texture &texture);

    explicit RenderComponent(const sf::Sprite &sprite);

    void setTexture(const sf::Texture &texture);

    void setSprite(const sf::Sprite &sprite);

    sf::Sprite &getRender();

    void cast() const override {};

    static sf::Sprite addSprite(const sf::Sprite &sprite);

    static sf::Sprite addFrame(const sf::Sprite &sprite);
};
