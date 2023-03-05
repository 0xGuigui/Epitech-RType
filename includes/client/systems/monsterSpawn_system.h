#pragma once

#include "client/systems/system.h"

class monsterSpawnSystem : public System {
private:
    int _spawnPositionX = 0;
    int _spawnPositionY = 0;
    int _monsterType = 0;
    int _spawnRate = 0;
    int _spawnTimer = 0;
    int _spawnCount = 0;
    int _maxSpawn = 0;
    int _monsterSpeedX = 0;
    int _monsterSpeedY = 0;
public:
    void update(sf::RenderWindow &window, World &world, float delta) override;

    void cast() const override {};
};
