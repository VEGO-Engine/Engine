#include "ProjectileComponent.h"

#include "CollisionHandler.h"
#include "Components.h"
#include "Entity.h"
#include "Game.h"
#include "HealthComponent.h"
#include "Vector2D.h"
#include <cassert>
#include <cstdio>

void ProjectileComponent::init() 
{
	transformComponent = &entity->getComponent<TransformComponent>();
    transformComponent->direction = direction;
    SoundManager::playSound(THROW_EGG);
}

void ProjectileComponent::update() 
{
    distance += speed;

    IntersectionBitSet boundsIntersection = Game::collisionHandler->getIntersectionWithBounds(entity);

    if ((boundsIntersection | IntersectionBitSet("1100")).all() || (boundsIntersection | IntersectionBitSet("0011")).all()) {
        this->entity->destroy();
        std::cout << "out of bounds" << std::endl;
    }

    if (distance > range) {
        this->entity->destroy();
        std::cout << "out of range" << std::endl;
    }

    Entity* player;
    if ((player = Game::collisionHandler->getAnyIntersection<Entity*>(
        entity,
        Vector2D(0,0),
        {GroupLabel::PLAYERS},
        {entity->getTeam()},
        true)) != nullptr) {
        player->getComponent<HealthComponent>().modifyHealth();
        this->entity->destroy();
    }
}