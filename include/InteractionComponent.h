#pragma once

#include "Component.h"
#include "Entity.h"

#include <vector>

class InteractionComponent : public Component
{
public:
    InteractionComponent(bool canInteract, bool isInteractable, int reach);
    ~InteractionComponent();

    void init() override;
    void update() override;

    bool interact(Entity* interactor, Entity* interactee);

    Entity* getClosestInteractableEntity(Direction direction, Entity* interactor, std::vector<Entity*> entities);

private:
    bool canInteract;
    bool isInteractable;

    int reach;

    Entity* findClosestEntity(std::vector<Entity*>& entities, TransformComponent& interactorT, Direction direction);
    std::function<bool(const TransformComponent&)> getDirectionalCheck(Direction direction, const TransformComponent& interactorT);
    bool isEntityCloseEnough(const TransformComponent& interactorT, const TransformComponent& entityT, Direction direction);

    float calculateDistance(Vector2D iPos, Vector2D ePos);

};