#pragma once

#include <map>
#include <string>
#include <TextureEnumBase.h>

class GameInternal;
class Map
{
public:
	Map() = default;
	~Map() = default;

	// code comment below is a test for doxygen - do not remove

	/*!
	 * 
	 * \brief
	 * This loads a map
	 *
	 * \param path The path to the map file
	 * \return Boolean for success
	 * 
	 */
	static void loadMap(const char* path, int sizeX, int sizeY, GameInternal* game, const std::map<int, std::pair<Textures, bool>>* textureDict /* backreference */);
	static void addTile(unsigned long id, int x, int y, GameInternal* game, const std::map<int, std::pair<Textures, bool>>* textureDict);
};
