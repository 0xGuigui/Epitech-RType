//
// Created by Guilhem Jéhanno on 04/02/2023.
//

#include "client/entities/entity.h"
#include "client/components/components.h"
#include "client/rtype.h"
#include "client/entities/powerup.h"
#include "client/entities/player.h"

static const sf::Rect<int> powerUpTypeSprite[] = {
        {12, 40, 16, 16},
        {41, 40, 16, 16},
        {69, 40, 16, 16},
        {98, 40, 16, 16},
};

PowerUp::PowerUp(powerupType powerUpType) : Entity() {
    sf::Sprite spr(rtype.textures.get("r-typesheet45"));
    spr.setTextureRect(powerUpTypeSprite[powerUpType]);

    addComponent<PositionComponent>(100, 150);
    addComponent<RenderComponent>(spr);
    addComponent<ScaleComponent>(2, 2);

    HitboxComponent hitboxComponent(spr, [this](std::shared_ptr<Entity> &e, const std::type_index &type) {
        this->eraseSelf();
    });
    hitboxComponent.setCollidables<Player>();
    addComponent<HitboxComponent>(hitboxComponent);
}


