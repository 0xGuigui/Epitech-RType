#include "client/utils/background.h"
#include "client/components/components.h"
#include "client/rtype.h"

Background::Background(const sf::RenderWindow &window) : Entity() {
    sf::Texture &back = rtype.textures.get("background");
    sf::Sprite background(back);

    addComponent<PositionComponent>(0, 0);
    addComponent<ScaleComponent>(static_cast<float>(window.getSize().x) / static_cast<float>(back.getSize().x), static_cast<float>(window.getSize().y) / static_cast<float>(back.getSize().y));
    addComponent<VelocityComponent>(-50, 0);
    addComponent<RenderComponent>(background);
}
