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

Entity* getClosestInteractableEntity(/*last direction key input*/ std::vector<Entity*> entities)
{
    // code to compare and find closest entity


}

bool InteractionComponent::interact(Entity* interactee)
{
    if(!interactee->hasComponent<InteractionComponent> || !interactee->getComponent<InteractionComponent>.isInteractable)
    {
        return false;
    }

    return true;

    // code to interact, basically 
}

// TODO:
// - find a way to determine which entities are interactible (bool, map?)
// - get the last saved key input => if two interactible entities, favour the one closer to last input/m
//   maybe only make the one in direction of last input interactible
// - add toggleable marker to show last direction => like stardew? (probably only possible once tmx + layers properly implemented)
// - add key input e for interact/maybe alt gr for other person?

