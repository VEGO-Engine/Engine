#include "InteractionComponent.h"

#include <algorithm>
#include <limits>

InteractionComponent::InteractionComponent(bool canInteract, bool isInteractable, int reach)
{
    this->canInteract = canInteract;
    this->isInteractable = isInteractable;
    this->reach = reach; // ofc that can be set individually, but its probably also okay if you just pass your entities width as its reach here methinks
}

InteractionComponent::~InteractionComponent() = default;

void InteractionComponent::init()
{

}

void InteractionComponent::update()
{

}

Entity* InteractionComponent::getClosestInteractableEntity(Direction direction, Entity* interactor, std::vector<Entity*> entities)
{
    // first kicking all the entities passed here that don't have the ability to be interacted with
    for (auto it = entities.begin(); it != entities.end(); it++)
    {
        if (!(*it)->hasComponent<InteractionComponent>() || !(*it)->getComponent<InteractionComponent>().isInteractable)
        {
            it = entities.erase(it);
            continue;
        }
    }

    // quick check if entities isn't empty
    if(entities.empty())
    {
        return nullptr;
    }

    // to reduce the amount of accesses to transformcomponent via getComponent()
    auto& interactorT = interactor->getComponent<TransformComponent>();

    // kick all entities that are either too far away or in the opposite direction, then calc distance and find closest entity that way
    Entity* entityToInteract = nullptr;

    switch(direction)
    {
        case Direction::LEFT: entityToInteract = findClosestEntityLeft(entities, interactorT);
            break;

        case Direction::RIGHT: entityToInteract = findClosestEntityRight(entities, interactorT);
            break;

        case Direction::UP: entityToInteract = findClosestEntityUp(entities, interactorT);
            break;

        case Direction::DOWN: entityToInteract = findClosestEntityDown(entities, interactorT);
            break;
    }

    return entityToInteract;
}

bool InteractionComponent::interact(Entity* interactor, Entity* interactee)
{
    if(!interactor->hasComponent<InteractionComponent>() || !interactor->getComponent<InteractionComponent>().canInteract)
    {
        throw std::logic_error("Interactor entity cannot interact");
    }

    if(!interactee->hasComponent<InteractionComponent>() || !interactee->getComponent<InteractionComponent>().isInteractable)
    {
        return false;
    }

    return true;
}

Entity* InteractionComponent::findClosestEntityLeft(std::vector<Entity*>& entities, TransformComponent& interactorT)
{
    Entity* closestEntity = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for(auto it = entities.begin(); it != entities.end(); it++)
    {
        auto& entityT = (*it)->getComponent<TransformComponent>();
        if(entityT.position.x > interactorT.position.x || !isEntityCloseEnoughLeft(interactorT.position, entityT.position, entityT.width))
        {
            it = entities.erase(it);
            continue;
        }

        float distance = calculateDistance(interactorT.position, entityT.position);

        if (distance < closestDistance) 
        {
            closestDistance = distance;
            closestEntity = *it;
        }
    }
    
    return closestEntity;
}

Entity* InteractionComponent::findClosestEntityRight(std::vector<Entity*>& entities, TransformComponent& interactorT)
{
    Entity* closestEntity = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for(auto it = entities.begin(); it != entities.end(); it++)
    {
        auto& entityT = (*it)->getComponent<TransformComponent>();
        if(entityT.position.x < interactorT.position.x || !isEntityCloseEnoughRight(interactorT.position, entityT.position, interactorT.width))
        {
            it = entities.erase(it);
            continue;
        }

        float distance = calculateDistance(interactorT.position, entityT.position);

        if (distance < closestDistance) 
        {
            closestDistance = distance;
            closestEntity = *it;
        }
    }

    return closestEntity;
}

Entity* InteractionComponent::findClosestEntityUp(std::vector<Entity*>& entities, TransformComponent& interactorT)
{
    Entity* closestEntity = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for(auto it = entities.begin(); it != entities.end(); it++)
    {
        auto& entityT = (*it)->getComponent<TransformComponent>();
        if(entityT.position.y < interactorT.position.y || !isEntityCloseEnoughUp(interactorT.position, entityT.position, entityT.height))
        {
            it = entities.erase(it);
            continue;
        }

        float distance = calculateDistance(interactorT.position, entityT.position);

        if (distance < closestDistance) 
        {
            closestDistance = distance;
            closestEntity = *it;
        }
    }

    return closestEntity;
}

Entity* InteractionComponent::findClosestEntityDown(std::vector<Entity*>& entities, TransformComponent& interactorT)
{
    Entity* closestEntity = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for(auto it = entities.begin(); it != entities.end(); it++)
    {
        auto& entityT = (*it)->getComponent<TransformComponent>();
        if(entityT.position.y > interactorT.position.y || !isEntityCloseEnoughDown(interactorT.position, entityT.position, interactorT.height))
        {
            it = entities.erase(it);
            continue;
        }

        float distance = calculateDistance(interactorT.position, entityT.position);

        if (distance < closestDistance) 
        {
            closestDistance = distance;
            closestEntity = *it;
        }
    }

    return closestEntity;
}

float InteractionComponent::calculateDistance(Vector2D iPos, Vector2D ePos)
{
    return std::abs(ePos.x - iPos.x) + std::abs(ePos.y - iPos.y);
}

bool InteractionComponent::isEntityCloseEnoughRight(Vector2D iPos, Vector2D ePos, int iWidth)
{
    if(ePos.x > ((int)iPos.x + (iWidth + reach)))
    {
        return false;
    }

    return true;
}

bool InteractionComponent::isEntityCloseEnoughLeft(Vector2D iPos, Vector2D ePos, int eWidth)
{
    if(ePos.x < ((int)iPos.x - (reach - eWidth)))
    {
        return false;
    }
    
    return true;
}

bool InteractionComponent::isEntityCloseEnoughUp(Vector2D iPos, Vector2D ePos, int eHeight)
{
    if(ePos.y < ((int)iPos.y - (reach - eHeight)))
    {
        return false;
    }

    return true;
}

bool InteractionComponent::isEntityCloseEnoughDown(Vector2D iPos, Vector2D ePos, int iHeight)
{
    if(ePos.y > ((int)iPos.y + (iHeight + reach)))
    {
        return false;
    }

    return true;
}