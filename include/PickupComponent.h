#pragma once

#include <functional>
#include "Component.h"

class PickupComponent : public Component
{
public:
	/**
	 * @brief Construct a new Powerup Component object
	 * @param func The function to be called when the powerup is picked up
	 */
	PickupComponent(std::function<void (Entity*)> func);
	~PickupComponent() {};

    void update(uint_fast16_t diffTime) override;

private:
    std::function<void (Entity*)> pickupFunc;
};