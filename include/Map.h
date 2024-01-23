#pragma once

class Map
{
public:
	Map() = default;
	~Map() = default;

	static void loadMap(const char* path, int sizeX, int sizeY);
};
