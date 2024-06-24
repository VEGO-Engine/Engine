#pragma once

#include <string>
#include <vector>

#include "Direction.h"
#include "Component.h"

class Manager;

class HealthComponent : public Component
{
public:

    HealthComponent(int health, Direction side, std::string healthTexture) : health(health), side(side), healthTexture(healthTexture) {}
    ~HealthComponent() {}

    void modifyHealth(int health = -1);
    void setHealth(int health);
    int getHealth() { return this->health; }

    void init() override;

    void refreshHearts();
    void createHeartComponents(int x);


private:

    int health;
    Direction side;
    std::string healthTexture;

    std::vector<Entity*> heartElements;
};