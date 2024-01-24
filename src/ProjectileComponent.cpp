#include "ProjectileComponent.h"

#include "Components.h"

void ProjectileComponent::init() 
{
	transformComponent = &entity->getComponent<TransformComponent>();
}

void ProjectileComponent::update() 
{
	transformComponent->velocity = velocity;

    distance += speed;

    if (distance > range) {
        entity->destroy();
        entity->getComponent<ColliderComponent>().removeCollision();
        //std::cout << "out of range" << std::endl;
    }
}