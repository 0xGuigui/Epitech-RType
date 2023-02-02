#include "client/components/render_component.h"

RenderComponent::RenderComponent(const sf::Texture &texture) {
    _render.setTexture(texture);
}

void RenderComponent::setTexture(const sf::Texture &texture) {
    _render.setTexture(texture);
}

sf::Sprite &RenderComponent::getRender() {
    return _render;
}
