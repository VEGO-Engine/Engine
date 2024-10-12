#pragma once

#include <functional>
#include "Component.h"

class PowerupComponent : public Component
{
public:
	PowerupComponent(std::function<void (Entity*)> func);
	~PowerupComponent() {};

	void update() override;

	std::string componentName() override { return "PowerupComponent"; }

private:
	std::function<void (Entity*)> pickupFunc;
};