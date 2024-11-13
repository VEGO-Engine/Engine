#pragma once

#include <functional>
#include "Component.h"

class PowerupComponent : public Component
{
public:
	PowerupComponent(std::function<void (Entity*)> func);
	~PowerupComponent() {};

	void update() override;

private:
	std::function<void (Entity*)> pickupFunc;
};