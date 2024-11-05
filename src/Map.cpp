#include "Map.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <type_traits>
#include <utility>
#include <vector>

#include <SDL_error.h>
#include <SDL_render.h>

#include <tmxlite/Layer.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Property.hpp>
#include <tmxlite/TileLayer.hpp>

#include "Constants.h"
#include "GameInternal.h"
#include "SpriteComponent.h"
#include "TextureManager.h"
#include "TileComponent.h"
#include "VEGO.h"
#include "tmxlite/Types.hpp"

void Map::loadMap(const char* path, int sizeX, int sizeY, GameInternal* game, const std::map<int, std::pair<std::string, bool>>* textureDict /* backreference */)
{
	std::string tileIDstr;
	char singleChar = 0;
	std::ifstream mapFile;
	mapFile.open(path);

	if (!mapFile.is_open()) {
		SDL_SetError("Error loading map: Couldn't open map file!");
		std::cout << "ERROR: Map couldnt be loaded! " << SDL_GetError() << std::endl;
		SDL_ClearError();
	}

	int x = 0, y = 0; // needed outside for-loop for error handling
	for (; !mapFile.eof(); mapFile.get(singleChar))
	{
		if (singleChar == ',' || singleChar == '\n') {
			if (tileIDstr.empty())
				continue;
			Map::addTile(std::stoi(tileIDstr), x * TILE_SIZE, y * TILE_SIZE, game, textureDict);
			tileIDstr.clear();
			x++;
			if (singleChar == '\n') {
				if (x != sizeX) {
					SDL_SetError("Error loading map: specified x size doesn't match map file!");
					std::cout << "ERROR: Map couldnt be loaded! " << SDL_GetError() << std::endl;
					SDL_ClearError();
				}
				x = 0;
				y++;
				continue;
			}
			continue;
		}
		if (!std::isdigit(singleChar)) continue;
		tileIDstr += singleChar;
	}
	if (y != sizeY) {
		SDL_SetError("Error loading map: specified y size doesn't match map file!");
		std::cout << "ERROR: Map couldnt be loaded! " << SDL_GetError() << std::endl;
		SDL_ClearError();
	}

	mapFile.close();
}

void Map::addTile(unsigned long id, int x, int y, GameInternal* game, const std::map<int, std::pair<std::string, bool>>* textureDict) // tile entity
{
	auto& tile(game->manager.addEntity());
	tile.addComponent<TileComponent>(x, y, TILE_SIZE, TILE_SIZE, id, textureDict);
	
	if(tile.getComponent<TileComponent>().hasCollision()) tile.addComponent<ColliderComponent>("tile"/*tile.getComponent<TileComponent>().getName().data()*/);
	tile.addGroup((size_t)Entity::GroupLabel::MAPTILES);
}

void Map::loadMapTmx(const char* path)
{
    tmx::Map map;
    if (!map.load(path)) {
        // TODO: log to console
    }

    const std::vector<tmx::Tileset>& tileSets = map.getTilesets();

    const std::vector<tmx::Layer::Ptr>& mapLayers = map.getLayers();
    const auto mapSize = map.getTileCount();
    const auto mapTileSize = map.getTileSize();

    std::vector<std::string> texturePaths = {};

    for (auto tileSet : tileSets) {
        texturePaths.emplace_back(tileSet.getImagePath());
    }

    for (auto& layer : mapLayers) {

        if (layer->getType() == tmx::Layer::Type::Tile) {
            auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();

            int zIndex = 0;

            const std::vector<tmx::Property>& properties = layer->getProperties();
            auto zIndexIterator = std::find_if(properties.begin(), properties.end(), [](const tmx::Property& property) {
                return property.getName() == "zIndex";
            });

            if (zIndexIterator != properties.end() && std::is_nothrow_convertible<decltype(zIndexIterator->getType()), int>::value) {
                zIndex = zIndexIterator->getIntValue();
            }

            const auto& tiles = tileLayer.getTiles();
            
            for (auto i = 0u; i < tileSets.size(); i++) {
                auto tilesetTexture = VEGO_Game().textureManager->loadTexture(texturePaths.at(i).c_str());
                tmx::Vector2i textureSize;
                SDL_QueryTexture(tilesetTexture, nullptr, nullptr, &(textureSize.x), &(textureSize.y));

                const auto tileCountX = textureSize.x / mapTileSize.x;
                const auto tileCountY = textureSize.y / mapTileSize.y;

                for (auto idx = 0ul; idx < mapSize.x * mapSize.y; idx++) {

                    if (idx >= tiles.size() || tiles[idx].ID < tileSets.at(i).getFirstGID()
                        || tiles[idx].ID >= (tileSets.at(i).getFirstGID() + tileSets.at(i).getTileCount())) {
                        continue;
                    }

                    const auto x = idx % mapSize.x;
                    const auto y = idx / mapSize.x;
                    
                    auto idIndex = (tiles[idx].ID - tileSets.at(i).getFirstGID());

                    int u = idIndex % tileCountX;
                    int v = idIndex / tileCountY;
                    u *= mapTileSize.x; //TODO we should be using the tile set size, as this may be different from the map's grid size
                    v *= mapTileSize.y;

                    //normalise the UV
                    u /= textureSize.x;
                    v /= textureSize.y;

                    //vert pos
                    const float tilePosX = static_cast<float>(x) * mapTileSize.x;
                    const float tilePosY = (static_cast<float>(y) * mapTileSize.y);

                    Map::addTile(tilePosX, tilePosY, mapTileSize, u, v, zIndex, texturePaths.at(i).c_str());
                }
            }
            if (layer->getType() == tmx::Layer::Type::Object) {
                // spawn objects
                continue;
            }
        }
    }
}

void Map::addTile(float x, float y, const tmx::Vector2u& mapTileSize, int u, int v, int zIndex, const char* texturePath)
{
    auto& tile(VEGO_Game().manager.addEntity());

    tile.addComponent<TransformComponent>(x, y, mapTileSize.x, mapTileSize.y, 1);
    tile.addComponent<SpriteComponent>(texturePath, v, u, zIndex); // why does uv need to be reversed?
}