#include "PowerupComponent.h"
#include "Game.h"
#include "CollisionHandler.h"
#include "Entity.h"
#include "HealthComponent.h"
#include "StatEffectsComponent.h"
#include "Constants.h"
#include <cstdint>

PowerupComponent::PowerupComponent(std::function<void (Entity*)> func)
{
    this->pickupFunc = func;
}

void  PowerupComponent::update()
{
    Entity* player;
    if ((player = this->entity->getManager().getGame()->collisionHandler->getAnyIntersection<Entity*>(
        entity,
        Vector2D(0, 0),
        { Entity::GroupLabel::PLAYERS },
        {},
        true)) != nullptr)
    {
        (this->pickupFunc)(player);
        this->entity->destroy();
    }
}