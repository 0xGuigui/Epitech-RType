#include "component.h"
#include "SFML/Graphics.hpp"

class RenderComponent : public Component {
private:
    sf::Sprite _render;
public:
    explicit RenderComponent(const sf::Texture &texture);

    void setTexture(const sf::Texture &texture);

    sf::Sprite &getRender();
};
