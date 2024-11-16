#pragma once

#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include <functional>
#include <tmxlite/Property.hpp>
#include <optional>
#include <tmxlite/Types.hpp>
#include <map>
#include <string>
#include <vector>

class GameInternal;
class Map
{
public:
	Map(const char* path);

	//[[deprecated("ID based text files are not supported anymore, use .tmx maps instead")]]
	//static void loadMap(const char* path, int sizeX, int sizeY, GameInternal* game, const std::map<int, std::pair<std::string, bool>>* textureDict /* backreference */);
	//[[deprecated]]
	//static void addTile(unsigned long id, int x, int y, GameInternal* game, const std::map<int, std::pair<std::string, bool>>* textureDict);

	/*!
	 * \brief Loads a .tmx map
	 * \param path Path to the `.tmx` map file
	 * 
	 */
	
	void generateTiles();
private:
	// required for initialisation
	struct MapData {
    	const std::vector<tmx::Tileset>* tileSets;
    	const std::vector<tmx::Layer::Ptr>* mapLayers;
    	const tmx::Vector2u* mapSize;
    	const tmx::Vector2u* mapTileSize;
    	const std::vector<std::string>* texturePaths;
	};

	struct TileSetData {
        const char* texturePath{};
        tmx::Vector2i textureSize;
        uint32_t tileCount{};
        tmx::Vector2u tileCount2D;
        uint32_t firstGID{};
    };

	tmx::Map map;
	Map::MapData mapData;
	std::vector<std::function<void()>> tileConstructors;

	void loadTileLayer(const tmx::TileLayer& layer);
	static void addTile(float x, float y, const tmx::Vector2u& mapTileSize, int u, int v, int zIndex, const char* texturePath, bool hasCollision);

	template<typename T>
	static std::optional<T> getLayerProperty(const std::vector<tmx::Property>& properties, std::string propertyName) { return std::nullopt; };
};