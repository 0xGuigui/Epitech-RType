#pragma once

class World;

class System {
    virtual void update(World &world, float delta) = 0;
    virtual ~System() = default;
};
