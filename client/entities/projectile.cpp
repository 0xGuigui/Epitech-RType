#include "client/entities/entities.h"
#include "client/components/components.h"
#include "client/rtype.h"
#include "client/entities/projectile.h"


Projectile::Projectile(const std::shared_ptr<Entity>& creator) : Entity() {
    _theCreator = creator;

    sf::Sprite spr(rtype.textures.get("r-typesheet1"));
    spr.setTextureRect({337, 255, 12, 4});

    addComponent<PositionComponent>(200, 500);
    addComponent<HealthComponent>(1, 40);
    addComponent<RenderComponent>(spr);
    addComponent<VelocityComponent>(100, 0);

    HitboxComponent hitboxComponent(spr, [this](std::shared_ptr<Entity> &e, const std::type_index &type) {
        if (_theCreator) {
            Entity &creatorType = *_theCreator;

            if (type == typeid(creatorType))
                return;
        }

        std::shared_ptr<HealthComponent> thisHealth = this->getComponent<HealthComponent>();
        std::shared_ptr<HealthComponent> healthComponent = e->getComponent<HealthComponent>();

        if (healthComponent)
            healthComponent->setHealth(healthComponent->getHealth() - thisHealth->getDamage());
        thisHealth->setHealth(0);
        this->eraseSelf();
    });
    hitboxComponent.setCollidables<Player, Monster>();
    addComponent<HitboxComponent>(hitboxComponent);
}

std::shared_ptr<Entity> Projectile::getCreator() {
    return _theCreator;
}

void Projectile::setCreator(const std::shared_ptr<Entity> &creator) {
    _theCreator = creator;
}
