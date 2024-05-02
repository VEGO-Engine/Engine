#include "Map.h"

#include <cctype>
#include <iostream>
#include <fstream>
#include <utility>

#include "Constants.h"
#include "Game.h"
#include "SDL_error.h"
#include "TileComponent.h"

void Map::loadMap(const char* path, int sizeX, int sizeY, Game* game, const std::map<int, std::pair<std::string, bool>>* textureDict /* backreference */)
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

void Map::addTile(unsigned long id, int x, int y, Game* game, const std::map<int, std::pair<std::string, bool>>* textureDict) // tile entity
{
	auto& tile(game->manager.addEntity());
	tile.addComponent<TileComponent>(x, y, TILE_SIZE, TILE_SIZE, id, textureDict);
	
	if(tile.getComponent<TileComponent>().hasCollision()) tile.addComponent<ColliderComponent>(tile.getComponent<TileComponent>().getName().data());
	tile.addGroup((size_t)Entity::GroupLabel::MAPTILES);
}