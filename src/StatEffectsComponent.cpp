#include "StatEffectsComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
// #include "KeyboardController.h"
#include <algorithm>
#include <iostream>

void StatEffectsComponent::init()
{}

void StatEffectsComponent::update(uint_fast16_t diffTime)
{
	for (int i = 0; i < MAX_STATS; i++)
	{
        this->buffs.at(i) -= diffTime;
		if (this->buffs.at(i) <= 0) {
			this->resetStatValue((Stats)i);
		}
	}
}

void StatEffectsComponent::modifyStatDur(Stats stat, int duration, int value)
{
	if(this->buffs.at((uint8_t)stat) == 0) this->modifyStatValue(stat, value);
	this->buffs.at((uint8_t)stat) += duration;
}

void StatEffectsComponent::modifyStatValue(Stats stat, int modifier) //modifier is basically there so the modifyfuncs in the components know if stats should be increased or decreased
{
	switch (stat)
	{
	case Stats::MOVEMENT_SPEED:
		this->entity->getComponent<TransformComponent>().modifySpeed(modifier);
		break;
	case Stats::ATTACK_SPEED:
		// this->entity->getComponent<KeyboardController>().modifyAtkSpeed(modifier);
		break;
	default: break;
	}
}

void StatEffectsComponent::resetStatValue(Stats stat)
{
	switch (stat)
	{
	case Stats::MOVEMENT_SPEED:
		this->entity->getComponent<TransformComponent>().resetSpeedMod();
		break;
	case Stats::ATTACK_SPEED:
		// this->entity->getComponent<KeyboardController>().resetAtkSpeedMod();
		break;
	default: break;
	}
}