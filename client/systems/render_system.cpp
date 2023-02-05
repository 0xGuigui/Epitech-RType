#include "client/world.h"
#include "client/systems/render_system.h"
#include "client/components/render_component.h"
#include "client/components/position_component.h"
#include "client/components/scale_component.h"
#include <iostream>

void RenderSystem::update(sf::RenderWindow &window, World &world, float delta) {
    std::vector<std::shared_ptr<Entity>> entities = world.getEntities<RenderComponent, PositionComponent>();

    for (const std::shared_ptr<Entity> &entity : entities) {
        std::shared_ptr<PositionComponent> position = entity->getComponent<PositionComponent>();
        std::shared_ptr<RenderComponent> render = entity->getComponent<RenderComponent>();
        std::shared_ptr<ScaleComponent> scale = entity->getComponent<ScaleComponent>();

        sf::Sprite &spr = render->getRender();
        if (scale) {
            //tried implementing an auto resizer
//            const sf::Vector2<float> dimensions = static_cast<sf::Vector2<float>>(spr.getTexture()->getSize());
//            spr.setScale((static_cast<float>(window.getSize().x) / dimensions.x) * scale->getScale().x, (static_cast<float>(window.getSize().y) / dimensions.y) * scale->getScale().y);
            spr.setScale(scale->getScale());
        }
        spr.setPosition(position->getPosition());

        window.draw(spr);
    }
}

