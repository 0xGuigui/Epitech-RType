#include "client/world.h"
#include "client/systems/movement_system.h"
#include "client/components/position_component.h"
#include "client/components/velocity_component.h"
#include "client/components/render_component.h"
#include "client/utils/background.h"

void MovementSystem::update(sf::RenderWindow &window, World &world, float delta) {
    std::vector<std::shared_ptr<Entity>> entities = world.getEntities<PositionComponent, VelocityComponent>();

    for (const std::shared_ptr<Entity>& entity : entities) {
        std::shared_ptr<PositionComponent> position = entity->getComponent<PositionComponent>();
        std::shared_ptr<VelocityComponent> velocity = entity->getComponent<VelocityComponent>();
        std::shared_ptr<RenderComponent> render = entity->getComponent<RenderComponent>();

        position->setPosition(
                position->getPosition().x + (velocity->getVelocity().x * delta),
                position->getPosition().y + (velocity->getVelocity().y * delta)
                );

        sf::Vector2<float> size = static_cast<sf::Vector2f>(window.getSize());
        if (render) {
            if (position->getPosition().x > size.x + ((size.x / 2) + render->getRender().getGlobalBounds().width) ||
            position->getPosition().x < -size.x - ((size.x / 2) + render->getRender().getGlobalBounds().width) ||
            position->getPosition().y > size.y + ((size.y / 2) + render->getRender().getGlobalBounds().height) ||
            position->getPosition().y < -size.y - ((size.y / 2) + render->getRender().getGlobalBounds().height)) {
                entity->eraseSelf();
            }
        } else if (position->getPosition().x > size.x * (size.x / 2) ||
                   position->getPosition().x < -size.x * -(size.x / 2) ||
                   position->getPosition().y > size.y * (size.y / 2) ||
                   position->getPosition().y < -size.y * -(size.y / 2)) {
            entity->eraseSelf();
        }
    }
}
