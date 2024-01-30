#pragma once
#include "Component.h"
#include "Constants.h"
#include <cstdint>
#include <array>

enum class Stats
{
	MOVEMENT_SPEED,
	ATTACK_SPEED
};

class StatEffectsComponent : public Component{
public:
	StatEffectsComponent() {};
	~StatEffectsComponent() {};

	void init() override;
	void update() override;

	void modifyStatDur(Stats stat, int duration);

	void modifyStatValue(Stats stat, int modifier);

private:
	std::array<int, MAX_STATS> buffs = { 0 };
};