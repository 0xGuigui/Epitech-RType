#include "client/world.h"
#include "client/systems/hitbox_system.h"
#include "client/components/hitbox_component.h"
#include "client/components/render_component.h"

void HitboxSystem::update(sf::RenderWindow &window, World &world, float delta) {
    std::vector<std::shared_ptr<Entity>> entities = world.getEntities<HitboxComponent, RenderComponent>();

    for (const std::shared_ptr<Entity>& entity : entities) {
        std::shared_ptr<RenderComponent> renderComponent = entity->getComponent<RenderComponent>();
        std::shared_ptr<HitboxComponent> hitboxComponent = entity->getComponent<HitboxComponent>();
        hitboxComponent->setHitbox(renderComponent->getRender().getGlobalBounds());
    }

    for (int i = 0; i < entities.size(); i++) {
        std::shared_ptr<HitboxComponent> hitboxComponent = entities[i]->getComponent<HitboxComponent>();

        for (int j = i + 1; j < entities.size(); i++) {
            std::shared_ptr<HitboxComponent> hitboxComponent2 = entities[j]->getComponent<HitboxComponent>();

            if (hitboxComponent->hitbox.intersects(hitboxComponent2->hitbox)) {
                //Check if entities[j]'s type is registered as collidable by entities[i]
                for (const std::type_index &index : hitboxComponent->collidableWith) {
                    if (index == typeid(entities[j]) || index == typeid(::Entity)) {
                        hitboxComponent->onCollide(entities[j]);
                        break;
                    }
                }
                //Check if entities[i]'s type is registered as collidable by entities[j]
                for (const std::type_index &index : hitboxComponent2->collidableWith) {
                    if (index == typeid(entities[i]) || index == typeid(::Entity)) {
                        hitboxComponent2->onCollide(entities[i]);
                        break;
                    }
                }
            }
        }
    }
}
