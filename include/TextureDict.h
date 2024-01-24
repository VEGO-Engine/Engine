#pragma once

#include <map>
#include <string>

class TextureDict
{
public:
	const std::map<int, std::string> textureDictionary = {
		{1, "assets/water.png"},
		{2, "assets/dirt.png"},
		{3, "assets/grass.png"},
		{7, "assets/grass_water_left.png"},
		{9, "assets/grass_water_right.png"}
	};
};
