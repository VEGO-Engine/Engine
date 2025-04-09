#include "PickupComponent.h"
#include "GameInternal.h"
#include "CollisionHandler.h"
#include "Entity.h"
#include "HealthComponent.h"
#include "SpriteComponent.h"
#include "StatEffectsComponent.h"
#include "Constants.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include <cstdint>
#include "VEGO.h"

PickupComponent::PickupComponent(std::function<void (Entity*)> func)
{
    this->pickupFunc = func;
}

void PickupComponent::update(uint_fast16_t diffTime)
{
    Entity* player;
    if ((player = this->entity->getManager().getGame()->collisionHandler->getAnyIntersection<Entity*>(
        entity,
        Vector2D(0, 0),
        { Entity::GroupLabel::PLAYERS })) != nullptr)
    {
        (this->pickupFunc)(player);
        this->entity->destroy();
    }
}