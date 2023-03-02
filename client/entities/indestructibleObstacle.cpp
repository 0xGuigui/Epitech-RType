#include "client/components/components.h"
#include "client/entities/entities.h"
#include "client/entities/indestructibleObstacle.h"
#include "client/rtype.h"

IndestructibleObstacle::IndestructibleObstacle() : Entity() {
    sf::Sprite spr(rtype.textures.get("r-typesheet28"));
    spr.setTextureRect({167, 3, 32, 13});

    addComponent<PositionComponent>(0, 0);
    addComponent<HealthComponent>(0);
    addComponent<RenderComponent>(spr);

    HitboxComponent hitboxComponent(spr, [this](std::shared_ptr<Entity> &e, const std::type_index &type) {
        std::shared_ptr<HealthComponent> healthComponent = e->getComponent<HealthComponent>();

        if (healthComponent) {
            std::shared_ptr<HealthComponent> thisHealth = getComponent<HealthComponent>();

            healthComponent->setHealth(healthComponent->getHealth() - thisHealth->getDamage());
        }
    });
    hitboxComponent.setCollidables<Projectile>();
    addComponent<HitboxComponent>(hitboxComponent);
}
