#include "StatEffectsComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "KeyboardController.h"
#include <algorithm>
#include <iostream>

void StatEffectsComponent::init()
{}

void StatEffectsComponent::update()
{
	/*int i = 0;
	std::transform(this->buffs.begin(), this->buffs.end(), this->buffs.begin(),
		[this, &i](uint8_t statDuration) {
			i++;
			uint8_t newDur = statDuration - 1;
			if (statDuration > 0 && newDur == 0) {
				if (statDuration > 1)
					std::cout << (int) statDuration << (int) newDur << std::endl;
				this->modifyStatValue((Stats)i, BUFF_VALUE * -1);
			}
			return newDur;
		});*/
	for (int i = 0; i < MAX_STATS; i++)
	{
		if (this->buffs.at(i) == 0) continue;
		if (this->buffs.at(i) - 1 == 0)
		{
			this->modifyStatValue((Stats)i, BUFF_VALUE * -1);
		}
		this->buffs.at(i) -= 1;
	}
}

void StatEffectsComponent::modifyStatDur(Stats stat, uint8_t duration)
{
	if(this->buffs.at((uint8_t)stat) == 0) this->modifyStatValue(stat, BUFF_VALUE);
	this->buffs.at((uint8_t)stat) += duration;
}

void StatEffectsComponent::modifyStatValue(Stats stat, int modifier)
{
	switch (stat)
	{
	case Stats::MOVEMENT_SPEED:
		this->entity->getComponent<TransformComponent>().modifySpeed(modifier);
		break;
	case Stats::ATTACK_SPEED:
		this->entity->getComponent<KeyboardController>().modifyAtkSpeed(modifier);
		break;
	default: break;
	}
}