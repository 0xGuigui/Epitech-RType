#include "client/entities/projectile.h"
#include "client/components/components.h"
#include "client/rtype.h"

Projectile::Projectile() : Entity() {
    sf::Sprite spr(rtype.textures.get("r-typesheet1.gif"));
    spr.setTextureRect({167, 3, 32, 13});

    addComponent<PositionComponent>(0, 0);
    addComponent<HealthComponent>(1);
    addComponent<RenderComponent>(spr);

    HitboxComponent hitboxComponent(spr, [this](std::shared_ptr<Entity> &e) {
        std::shared_ptr<HealthComponent> healthComponent = this->getComponent<HealthComponent>();

        healthComponent->setHealth(0);
        this->eraseSelf();
    });
    addComponent<HitboxComponent>(hitboxComponent);
}
