#pragma once

#include "Component.h"
#include "InteractionListener.h"

#include <functional>

class InteractionComponent : public Component, public InteractionListener
{
public:
    /**
     * @brief Constructor for the InteractionComponent.
     * @param callback A function to be called when an interaction event is triggered. void* actor, void* data are passed to the callback function from InteractionEventdataStruct.
     */
    InteractionComponent(std::function<void(void*,void*)> callback);

    /**
     * @brief Internal function to be called when an interaction event is triggered.
     */
    void interact(void* actor, void* data) override;

    /**
     * @brief Internal function to use as reference for targeting.
     */
    std::shared_ptr<Vector2D> getPosition() override;
private:
    std::function<void(void*,void*)> interactionCallback;
};