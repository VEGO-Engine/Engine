#include "StatEffectsComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <algorithm>
#include <iostream>

void StatEffectsComponent::init()
{}

void StatEffectsComponent::update()
{
	uint32_t currentTime = SDL_GetTicks();
	for (auto it = effects.begin(); it != effects.end(); ) {
		uint32_t elapsedTime = currentTime - it->startTime;
		
		if (elapsedTime >= it->duration) {
			it->resetFunction();
			it = effects.erase(it);
			continue;
		}
		it++;
    }
}

void StatEffectsComponent::addEffect(uint32_t duration, std::function<void()> resetFunction) {
	uint32_t startTime = SDL_GetTicks();
    effects.push_back({duration, resetFunction, startTime});
}