#pragma once

#include "Component.h"

class Manager;

class HealthComponent : public Component
{
public:

    HealthComponent(int health, Manager* manager, bool player) : health(health), manager(manager), player(player) {}
    ~HealthComponent() {}

    void getDamage() { this->health--; }
    int getHealth() { return this->health; }

    void init() override;

    void createAllHearts();
    void createHeartComponents(int x);

    void setHealth(int health) {this->health = health;}


private:

    int health;
    Manager* manager;
    bool player; //true if player1 / false if player2

};