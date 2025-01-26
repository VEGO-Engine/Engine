#pragma once
#include "Component.h"
#include "Constants.h"
#include <cstdint>
#include <array>
#include <functional>

// This acts as a manager for the lifetime of a stateffect
struct StatEffect {
    uint32_t duration;
    std::function<void()> resetFunction;
    uint32_t startTime;
};

class StatEffectsComponent : public Component{
public:
	StatEffectsComponent() {};
	~StatEffectsComponent() {};

	void init() override;
	void update() override;
	void addEffect(uint32_t duration, std::function<void()> resetFunction);

private:
	std::vector<StatEffect> effects = {};
};