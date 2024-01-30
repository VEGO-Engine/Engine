#pragma once

#include <map>
#include <string>
#include "AssetManager.h"

class TextureDict
{
public:
	const std::map<int, std::string> tileDictionary = {
		{1, "assets/water.png"},
		{2, "assets/dirt.png"},
		{3, "assets/grass.png"},
		{7, "assets/grass_water_left.png"},
		{9, "assets/grass_water_right.png"}
	};


	std::map<PowerupType, std::string> powerupDictionary = {
		{PowerupType::HEART, "assets/heart_powerup.png"},
		{PowerupType::WALKINGSPEED, "assets/movement_speed_powerup.png"},
		{PowerupType::SHOOTINGSPEED, "assets/atk_speed_powerup.png"}
	};
};
