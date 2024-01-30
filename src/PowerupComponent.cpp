#include "PowerupComponent.h"
#include "Game.h"
#include "CollisionHandler.h"
#include "Entity.h"
#include "HealthComponent.h"
#include "StatEffectsComponent.h"
#include "Constants.h"
#include <cstdint>

PowerupComponent::PowerupComponent(PowerupType type)
{
    switch (type)
    {
    case PowerupType::HEART:
        this->pickupFunc = (&PowerupComponent::heartEffect);
        break;
    case PowerupType::WALKINGSPEED:
        this->pickupFunc = (&PowerupComponent::movementSpeedEffect);
        break;
    case PowerupType::SHOOTINGSPEED:
        this->pickupFunc = (&PowerupComponent::atkSpeedEffect);
        break;
    default:
        break;
    }
}

void  PowerupComponent::update()
{
    Entity* player;
    if ((player = Game::collisionHandler->getAnyIntersection<Entity*>(
        entity,
        Vector2D(0, 0),
        { GroupLabel::PLAYERS },
        {},
        true)) != nullptr)
    {
        (this->*pickupFunc)(player);
        this->entity->destroy();
    }
}

void PowerupComponent::heartEffect(Entity* player)
{
    if(player->getComponent<HealthComponent>().getHealth() < 5)
        player->getComponent<HealthComponent>().modifyHealth(1);
}

void PowerupComponent::movementSpeedEffect(Entity* player)
{
    player->getComponent<StatEffectsComponent>().modifyStatDur(Stats::MOVEMENT_SPEED, BUFF_DURATION);
}

void PowerupComponent::atkSpeedEffect(Entity* player)
{
    player->getComponent<StatEffectsComponent>().modifyStatDur(Stats::ATTACK_SPEED, BUFF_DURATION);
}