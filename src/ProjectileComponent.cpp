#include "ProjectileComponent.h"

#include "CollisionHandler.h"
#include "SoundManager.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "GameInternal.h"
#include "HealthComponent.h"
#include "Vector2D.h"
#include <cassert>
#include <cstdio>

void ProjectileComponent::init() 
{
	transformComponent = &entity->getComponent<TransformComponent>();
    transformComponent->direction = direction;
    SoundManager::playSound(this->entity->getManager().getGame(), THROW_EGG);
}

void ProjectileComponent::update() 
{
    distance += speed;

    IntersectionBitSet boundsIntersection = this->entity->getManager().getGame()->collisionHandler->getIntersectionWithBounds(entity);

    if ((boundsIntersection | IntersectionBitSet("1100")).all() || (boundsIntersection | IntersectionBitSet("0011")).all()) {
        this->entity->destroy();
    }

    if (distance > range) {
        this->entity->destroy();
    }

    Entity* player;
    if ((player = this->entity->getManager().getGame()->collisionHandler->getAnyIntersection<Entity*>(
        entity,
        Vector2D(0,0),
        {Entity::GroupLabel::PLAYERS},
        {this->owner})) != nullptr) {
        player->getComponent<HealthComponent>().modifyHealth();
        this->entity->destroy();
    }
}