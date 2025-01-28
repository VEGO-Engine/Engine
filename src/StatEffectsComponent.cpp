#include "StatEffectsComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include <algorithm>
#include <iostream>

void StatEffectsComponent::init()
{}

void StatEffectsComponent::update(uint_fast16_t diffTime)
{
	for (auto it = effects.begin(); it != effects.end(); ) {
		it->duration -= diffTime;
		
		if (it->duration <= 0) {
			it->resetFunction();
			it = effects.erase(it);
			continue;
		}
		it++;
    }
}

void StatEffectsComponent::addEffect(uint32_t duration, std::function<void()> resetFunction) {
    effects.push_back({duration, resetFunction});
}