#include "client/systems/hitbox_system.h"
#include "client/components/hitbox_component.h"
#include "client/components/render_component.h"
#include "client/entities/entity.h"
#include "client/world.h"

void HitboxSystem::update(World &world, float delta) {
    std::vector<std::shared_ptr<Entity>> entities = world.getEntities<HitboxComponent, RenderComponent>();

    for (const std::shared_ptr<Entity>& entity : entities) {
        std::shared_ptr<RenderComponent> renderComponent = entity->getComponent<RenderComponent>();
        std::shared_ptr<HitboxComponent> hitboxComponent = entity->getComponent<HitboxComponent>();
        hitboxComponent->setHitbox(renderComponent->render.getGlobalBounds());
    }
    for (int i = 0; i < entities.size(); i++) {
        std::shared_ptr<HitboxComponent> hitboxComponent = entities[i]->getComponent<HitboxComponent>();

        for (int j = i + 1; j < entities.size(); i++) {
            std::shared_ptr<HitboxComponent> hitboxComponent2 = entities[j]->getComponent<HitboxComponent>();

            if (hitboxComponent->hitbox.intersects(hitboxComponent2->hitbox)) {
                hitboxComponent->onCollide();
                hitboxComponent2->onCollide();
            }
        }
    }
}
