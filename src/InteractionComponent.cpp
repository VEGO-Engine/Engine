#include "InteractionComponent.h"

#include "VEGO.h"

InteractionComponent::InteractionComponent(std::function<void(void*,void*)> callback) : interactionCallback(callback)
{
    VEGO_Game().interactionManager->registerListener(this->entity->getComponentAsPointer<InteractionComponent>());
}

void InteractionComponent::interact(void* actor, void* data)
{
    if (interactionCallback) {
        interactionCallback(actor, data);
    }
}
std::shared_ptr<Vector2D> InteractionComponent::getPosition() // required for targeting strategy, return null to only allow explicit targeting
{
    if (entity->hasComponent<TransformComponent>()) {
        return std::make_shared<Vector2D>(entity->getComponent<TransformComponent>().position);
    }
    return nullptr;
}