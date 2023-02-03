//
// Created by Guilhem Jéhanno on 03/02/2023.
//

#include "client/entities/monsters.h"
#include "client/components/components.h"
#include "client/rtype.h"

static const sf::Rect<int> monsterTypeSprite[] = {
        {1, 2, 16, 12},
        {5, 6, 21, 24},
        {1, 4, 32, 29},
        {7, 7, 22, 22},
};

static const std::string monsterSpritePath[] = {
        "r-typesheet3",
        "r-typesheet5",
        "r-typesheet7",
        "r-typesheet8",
};

Monsters::Monsters( monstersType monsterType) : Entity() {
    sf::Sprite spr(rtype.textures.get(monsterSpritePath[monsterType]));
    spr.setTextureRect(monsterTypeSprite[monsterType]);

    addComponent<PositionComponent>(200, 200);
    addComponent<HealthComponent>(100, 100);
    addComponent<RenderComponent>(spr);
    addComponent<ScaleComponent>(5, 5);

    HitboxComponent hitboxComponent(spr, [this](std::shared_ptr<Entity> &e) {
        std::shared_ptr<HealthComponent> healthComponent = e->getComponent<HealthComponent>();

        if (healthComponent) {
            std::shared_ptr<HealthComponent> thisHealth = getComponent<HealthComponent>();

            thisHealth->setHealth(thisHealth->health - healthComponent->damage);
        }
    });
    addComponent<HitboxComponent>(hitboxComponent);
}
