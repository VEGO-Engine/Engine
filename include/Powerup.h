#pragma once

#include "Component.h"
#include "Manager.h"
#include "Vector2D.h"
#include <map>

enum class PowerupType
{
	HEART,
	WALKINGSPEED,
	SHOOTINGSPEED
};

class Powerup
{
public:
	Powerup(){}
	~Powerup(){}

	static Vector2D calculateSpawnPosition();
	static PowerupType calculateType();

private:
	Manager* manager;
};