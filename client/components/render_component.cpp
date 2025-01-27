#include "client/components/render_component.h"

RenderComponent::RenderComponent(const sf::Texture &texture) {
    _render.setTexture(texture);
}

RenderComponent::RenderComponent(const sf::Sprite &sprite) {
    _render = sprite;
}

void RenderComponent::setTexture(const sf::Texture &texture) {
    _render.setTexture(texture);
}

sf::Sprite &RenderComponent::getRender() {
    return _render;
}

void RenderComponent::setSprite(const sf::Sprite &sprite) {
    _render = sprite;
}

sf::Sprite RenderComponent::addSprite(const sf::Sprite &sprite) {
    return {sprite};
}

sf::Sprite RenderComponent::addFrame(const sf::Sprite &sprite) {
    return {sprite};
}

sf::Sprite addFrame(const sf::Sprite &sprite) {
    return sprite;
}
