#pragma once

#include <map>
#include <string>
#include "Powerup.h"

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
		{PowerupType::HEART, "assets/heart.png"},
		{PowerupType::WALKINGSPEED, "assets/heart.png"},
		{PowerupType::SHOOTINGSPEED, "assets/heart.png"}
	};
};
