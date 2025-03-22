#pragma once

#include <functional>
#include "Component.h"
#include "InteractionListener.h"

class PowerupComponent : public Component, public InteractionListener
{
public:
    /**
     * @brief Construct a new Powerup Component object
     * @param func The function to be called when the powerup is picked up
     */
    PowerupComponent(std::function<void (Entity*)> func);
    ~PowerupComponent() {};

    void update(uint_fast16_t diffTime) override;


    void interact(void* actor, void* data) override;
    std::shared_ptr<Vector2D> getPosition() override;

private:
    std::function<void (Entity*)> pickupFunc;
};