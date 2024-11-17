#pragma once

#include <tmxlite/Types.hpp>
#include <map>
#include <string>

class GameInternal;
class Map
{
public:
	Map() = default;
	~Map() = default;

	/*!
	 * 
	 * \brief
	 * This loads a map
	 *
	 * \param path The path to the map file
	 * \return Boolean for success
	 * 
	 */
	[[deprecated("ID based text files are not supported anymore, use .txm maps instead")]]
	static void loadMap(const char* path, int sizeX, int sizeY, GameInternal* game, const std::map<int, std::pair<std::string, bool>>* textureDict /* backreference */);
	[[deprecated]]
	static void addTile(unsigned long id, int x, int y, GameInternal* game, const std::map<int, std::pair<std::string, bool>>* textureDict);

	/*!
	 * \brief Loads a .tmx map
	 * \param path Path to the `.tmx` map file
	 * 
	 */
	static void loadMapTmx(const char* path);
private:
	static void addTile(float x, float y, const tmx::Vector2u& mapTileSize, int u, int v, int zIndex, const char* texturePath);
};
