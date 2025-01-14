#include "InteractionComponent.h"

#include <algorithm>
#include <limits>

InteractionComponent::InteractionComponent(bool canInteract, bool isInteractable, int reach)
        : canInteract(canInteract), isInteractable(isInteractable), reach(reach) {}

InteractionComponent::~InteractionComponent() = default;

void InteractionComponent::init() {}

void InteractionComponent::update() {}

bool InteractionComponent::interact(Entity* interactor, Entity* interactee)
{
    if(!interactor->hasComponent<InteractionComponent>() || !interactor->getComponent<InteractionComponent>().canInteract)
        throw std::logic_error("Interactor entity cannot interact");

    if(!interactee->hasComponent<InteractionComponent>() || !interactee->getComponent<InteractionComponent>().isInteractable)
        return false;

    return true;
}

Entity* InteractionComponent::getClosestInteractableEntity(Direction direction, Entity* interactor, std::vector<Entity*> entities)
{
    entities.erase(std::remove_if(entities.begin(), entities.end(), [](Entity* e) {
        return !e->hasComponent<InteractionComponent>() || !e->getComponent<InteractionComponent>().isInteractable;
    }), entities.end());

    if(entities.empty())
        return nullptr;

    auto& interactorT = interactor->getComponent<TransformComponent>();
    return findClosestEntity(entities, interactorT, direction);
}

Entity* InteractionComponent::findClosestEntity(std::vector<Entity*>& entities, TransformComponent& interactorT, Direction direction)
{
    Entity* closestEntity = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    auto isInDirection = getDirectionalCheck(direction, interactorT);

    entities.erase(std::remove_if(entities.begin(), entities.end(), [&](Entity* e){
        auto& entityT = e->getComponent<TransformComponent>();
        return !isInDirection(entityT) || !isEntityCloseEnough(interactorT, entityT, direction);
    }), entities.end());

    for(auto e : entities)
    {
        auto& entityT = e->getComponent<TransformComponent>();
        float distance = calculateDistance(interactorT.position, entityT.position);

        if (distance < closestDistance) {
            closestDistance = distance;
            closestEntity = e;
        }
    }

    return closestEntity;
}

std::function<bool(const TransformComponent&)> InteractionComponent::getDirectionalCheck(Direction direction, const TransformComponent& interactorT)
{
    switch(direction)
    {
        case Direction::LEFT:
            return[&interactorT](const TransformComponent& entityT) {
                return entityT.position.x < interactorT.position.x;
            };
        case Direction::RIGHT:
            return[&interactorT](const TransformComponent& entityT) {
                return entityT.position.x > interactorT.position.x;
            };
        case Direction::UP:
            return[&interactorT](const TransformComponent& entityT) {
                return entityT.position.y < interactorT.position.y;
            };
        case Direction::DOWN:
            return[&interactorT](const TransformComponent& entityT) {
                return entityT.position.y > interactorT.position.y;
            };
        default:
            return [](const TransformComponent&) { return false; };
    }
}

bool InteractionComponent::isEntityCloseEnough(const TransformComponent& interactorT, const TransformComponent& entityT, Direction direction)
{
    switch (direction)
    {
        case Direction::LEFT:
            return (entityT.position.x >= (interactorT.position.x - reach));
        case Direction::RIGHT:
            return (entityT.position.x <= (interactorT.position.x + reach));
        case Direction::UP:
            return (entityT.position.y >= (interactorT.position.y - reach));
        case Direction::DOWN:
            return (entityT.position.y <= (interactorT.position.y + reach));
        default:
            return false;
    }
}

float InteractionComponent::calculateDistance(Vector2D iPos, Vector2D ePos)
{
    return std::abs(ePos.x - iPos.x) + std::abs(ePos.y - iPos.y);
}