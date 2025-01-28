#pragma once
#include "Component.h"
#include "Constants.h"
#include <cstdint>
#include <array>
#include <functional>

/**
 * @brief Struct to hold the duration, reset function and start time of a stat effect
 */
struct StatEffect {
    uint32_t duration; //!< Duration of the effect in milliseconds
    std::function<void()> resetFunction; //!< Function to reset the effect, will be called on expiry of duration
    uint32_t startTime;
};

class StatEffectsComponent : public Component{
public:
	StatEffectsComponent() {};
	~StatEffectsComponent() {};

	void init() override;
	void update() override;
	/**
	 * @brief Add a stat effect to the entity
	 * @param duration The duration of the effect in milliseconds
	 * @param resetFunction The function to reset the effect, will be called on expiry of duration
	 */
	void addEffect(uint32_t duration, std::function<void()> resetFunction);

private:
	std::vector<StatEffect> effects = {};
};