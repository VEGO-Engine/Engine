#pragma once

#include <functional>
#include "Component.h"

//! \brief PickupComponent class to handle pickup events
//! \details This class manages pickup events, allowing for the registration of a callback function to be called when an entity with this component collides with another entity that has the "players" group label.
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