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

    Entity* getClosestInteractableEntity(Key directionKey, Entity* interactor, std::vector<Entity*> entities);
    bool interact(Entity* interactor, Entity* interactee);
    
private:
    bool canInteract;
    bool isInteractable;

    int reach;

    bool isEntityCloseEnoughRight(Vector2D iPos, Vector2D ePos, int iWidth);
    bool isEntityCloseEnoughLeft(Vector2D iPos, Vector2D ePos, int eWidth);
    bool isEntityCloseEnoughUp(Vector2D iPos, Vector2D ePos, int eHeight);
    bool isEntityCloseEnoughDown(Vector2D iPos, Vector2D ePos, int iHeight);
};