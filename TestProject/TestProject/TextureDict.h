#pragma once
#include <map>
#include <string>

class TextureDict
{
public:
	const std::map<int, const char*> textureDictionary =
	{
		{0, "assets/water.png"},
		{1, "assets/dirt.png"},
		{2, "assets/grass.png"}
	};
};
