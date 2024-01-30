#pragma once

#include "Component.h"
#include "AssetManager.h"

class PowerupComponent : public Component
{
public:
	PowerupComponent(PowerupType type);
	~PowerupComponent() {};

	void update() override;
	void heartEffect(Entity* player);
	void movementSpeedEffect(Entity* player);
	void atkSpeedEffect(Entity* player);

private:
	void (PowerupComponent::*pickupFunc)(Entity* player);
};