#pragma once

#include "Component.h"
#include "Entity.h"

#include <vector>

class InteractionComponent : public Component
{
public:
    InteractionComponent(bool canInteract, bool isInteractable);
    ~InteractionComponent();

    void init() override;
    void update() override;

    Entity* getClosestInteractableEntity(Key directionKey, Entity* interactor, std::vector<Entity*> entities);
    bool interact(Entity* interactor, Entity* interactee);
    
private:
    bool canInteract;
    bool isInteractable;
};