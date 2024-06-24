#include "HealthComponent.h"

#include "Direction.h"
#include "Entity.h"
#include "GameInternal.h"
#include <cstdio>

void HealthComponent::init() 
{}

void HealthComponent::modifyHealth(int health) 
{
    this->health += health;
}

void HealthComponent::setHealth(int health) 
{
    this->health = health;
}