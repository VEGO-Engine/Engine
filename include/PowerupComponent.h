#pragma once

#include <functional>
#include "Component.h"

class PowerupComponent : public Component
{
public:
	PowerupComponent(std::function<void (Entity*)> func);
	~PowerupComponent() {};

	void update(uint_fast16_t diffTime) override;

private:
	std::function<void (Entity*)> pickupFunc;
};