#include "InteractionComponent.h"

InteractionComponent::InteractionComponent(bool canInteract, bool isInteractable)
{
    this->canInteract = canInteract;
    this->isInteractable = isInteractable;
}

InteractionComponent::~InteractionComponent() = default;

void InteractionComponent::init()
{

}

void InteractionComponent::update()
{

}

Entity* getClosestInteractableEntity(Key directionKey, Entity* interactor, std::vector<Entity*> entities)
{
    for(auto e : entities)
    {
        if(!e->hasComponent<InteractionComponent>() || !e->getComponent<InteractionComponent>().isInteractable)
        {
            auto it = std::remove(entities.begin(), entities.end(), e);
            entities.erase(it, entities.end());
        }
    }

    if(entities.empty())
    {
        return nullptr;
    }

    for(auto e : entities)
    {
        if(e->getComponent<TransformComponent>().position.x)
    }
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

// TODO:
// - get the last saved key input => if two interactible entities, favour the one closer to last input/
//   maybe only make the one in direction of last input interactible, or if two entities are ex. left and right and the last
//   input was down, then either try to calc the closer one or if theyre the same distance away, favour one side automatically
// - add toggleable marker to show last direction => like stardew? (probably only possible once tmx + layers properly implemented)
// - add key input e for interact/maybe alt gr for other person?

