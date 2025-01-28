#pragma once

#include <functional>
#include "Component.h"

class PowerupComponent : public Component
{
public:
	/**
	 * @brief Construct a new Powerup Component object
	 * @param func The function to be called when the powerup is picked up
	 */
	PowerupComponent(std::function<void (Entity*)> func);
	~PowerupComponent() {};

	void update() override;

private:
	std::function<void (Entity*)> pickupFunc;
};