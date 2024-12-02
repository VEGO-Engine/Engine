#pragma once

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include <tmxlite/Map.hpp>
#include <tmxlite/Property.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Types.hpp>

class GameInternal;
class Map
{
public:
	/*!
	 * \brief Loads a .tmx map
	 * \details Loads a `.tmx` file and extracts all relevant data. Any entities (including tiles) are only spawned once
	 * \param path Path to the `.tmx` map file
	 * \sa Map::generateTiles()
	 */
	Map(const char* path);
	void generateTiles(); //!< Generates the map based on the loaded definition
private:
	// struct required for initialisation
	struct MapData {
		const std::vector<tmx::Tileset>* tileSets;
		const std::vector<tmx::Layer::Ptr>* mapLayers;
		const tmx::Vector2u* mapSize;
		const tmx::Vector2u* mapTileSize;
		const std::vector<std::string>* texturePaths;
	};

	struct TileSetData {
		std::string texturePath{};
		tmx::Vector2f textureSize;
		uint32_t tileCount{};
		tmx::Vector2u tileCount2D;
		uint32_t firstGID{};
	};

	tmx::Map map;
	Map::MapData mapData;
	std::vector<std::function<void()>> tileConstructors;

	void loadTileLayer(const tmx::TileLayer& layer);
	static void addTile(float x, float y, const tmx::Vector2u& mapTileSize, int u, int v, int zIndex, std::string texturePath, bool hasCollision);

	template<typename T>
	static std::optional<T> getLayerProperty(const std::vector<tmx::Property>& properties, std::string propertyName) { return std::nullopt; };
};