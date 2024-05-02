#pragma once

#include <map>
#include <string>

class Game;
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
	static void loadMap(const char* path, int sizeX, int sizeY, Game* game, const std::map<int, std::pair<std::string, bool>>* textureDict /* backreference */);
	static void addTile(unsigned long id, int x, int y, Game* game, const std::map<int, std::pair<std::string, bool>>* textureDict);
};
