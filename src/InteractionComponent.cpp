#include "InteractionComponent.h"

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

Entity* InteractionComponent::getClosestInteractableEntity(Key directionKey, Entity* interactor, std::vector<Entity*> entities)
{
    // first kicking all the entities passed here that don't have the ability to be interacted with
    for (auto it = entities.begin(); it != entities.end();)
    {
        if (!(*it)->hasComponent<InteractionComponent>() || !(*it)->getComponent<InteractionComponent>().isInteractable)
        {
            it = entities.erase(it);
            continue;
        }

        it++;
    }

    // quick check if entities isn't empty
    if(entities.empty())
    {
        return nullptr;
    }

    // to reduce the amount of accesses to transformcomponent via getComponent()
    auto& interactorT = interactor->getComponent<TransformComponent>();

    // kicking all entities that are too far away, disgusting code that i dont even know if it works just yet but oh well
    for (auto it = entities.begin(); it != entities.end();)
    {
        auto& entityT = (*it)->getComponent<TransformComponent>();

        if(((entityT.position.x >= interactorT.position.x) && !isEntityCloseEnoughRight(interactorT.position, entityT.position, interactorT.width)) ||
           ((entityT.position.x <= interactorT.position.x) && !isEntityCloseEnoughLeft(interactorT.position, entityT.position, entityT.width)) ||
           ((entityT.position.y <= interactorT.position.y) && !isEntityCloseEnoughUp(interactorT.position, entityT.position, entityT.height)) ||
           ((entityT.position.y >= interactorT.position.y) && !isEntityCloseEnoughDown(interactorT.position, entityT.position, interactorT.height)))
        {
            it = entities.erase(it);
            continue;
        }

        it++;
    }

    // check if entities is empty
    if(entities.empty())
    {
        return nullptr;
    }

    // then check whichever entitiy is closer, based on direction i guess? so if direction left then the entity on the left, if direction down then entity on down???? i guess?????
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

bool InteractionComponent::isEntityCloseEnoughDown(Entity* i, Entity* e)
{
    if(ePos.y > ((int)iPos.y + (iHeight + reach)))
    {
        return false;
    }

    return true;
}