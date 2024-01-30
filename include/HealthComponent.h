#pragma once

#include "Direction.h"
#include "Component.h"

class Manager;

class HealthComponent : public Component
{
public:

    HealthComponent(int health, Direction side) : health(health), side(side) {}
    ~HealthComponent() {}

    void modifyHealth(int health = -1);
    int getHealth() { return this->health; }

    void init() override;

    void refreshHearts();
    void createHeartComponents(int x);

private:

    int health;
    Direction side;
};