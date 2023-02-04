#include "client/world.h"
#include "client/systems/hitbox_system.h"
#include "client/components/components.h"

void HitboxSystem::update(sf::RenderWindow &window, World &world, float delta) {
    std::vector<std::shared_ptr<Entity>> entities = world.getEntities<HitboxComponent, RenderComponent, PositionComponent>();

    for (const std::shared_ptr<Entity>& entity : entities) {
        std::shared_ptr<RenderComponent> renderComponent = entity->getComponent<RenderComponent>();
        std::shared_ptr<HitboxComponent> hitboxComponent = entity->getComponent<HitboxComponent>();
        std::shared_ptr<PositionComponent> positionComponent = entity->getComponent<PositionComponent>();

        sf::Rect<float> rect = renderComponent->getRender().getGlobalBounds();
        const sf::Vector2<float> &position = positionComponent->getPosition();

        rect.top = position.y;
        rect.left = position.x;

        hitboxComponent->setHitbox(rect);
    }

    for (int i = 0; i < entities.size(); i++) {
        std::shared_ptr<HitboxComponent> hitboxComponent = entities[i]->getComponent<HitboxComponent>();

        for (int j = i + 1; j < entities.size(); j++) {
            std::shared_ptr<HitboxComponent> hitboxComponent2 = entities[j]->getComponent<HitboxComponent>();

            if (hitboxComponent->getHitbox().intersects(hitboxComponent2->getHitbox())) {
                //Check if entities[j]'s type is registered as collidable by entities[i]
                for (const std::type_index index : hitboxComponent->getCollidables()) {
                    Entity &type = *entities[j].get();
                    if (index == typeid(type) || index == typeid(Entity)) {
                        hitboxComponent->onCollide(entities[j]);
                        break;
                    }
                }
                //Check if entities[i]'s type is registered as collidable by entities[j]
                for (const std::type_index index : hitboxComponent2->getCollidables()) {
                    Entity &type = *entities[i].get();
                    if (index == typeid(type) || index == typeid(Entity)) {
                        hitboxComponent2->onCollide(entities[i]);
                        break;
                    }
                }
            }
        }
    }
}
