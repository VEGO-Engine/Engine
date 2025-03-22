#include "PowerupComponent.h"
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

PowerupComponent::PowerupComponent(std::function<void (Entity*)> func)
{
    this->pickupFunc = func;
}

void  PowerupComponent::update(uint_fast16_t diffTime)
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


void PowerupComponent::interact(void* actor, void* data)
{
    std::cout << VEGO_Game().textureManager->getTexturePath(this->entity->getComponent<SpriteComponent>().getTexture()) << std::endl;
}


std::shared_ptr<Vector2D> PowerupComponent::getPosition()
{
    return std::make_shared<Vector2D>(this->entity->getComponent<TransformComponent>().position);
}