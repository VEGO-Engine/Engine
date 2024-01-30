#include "Map.h"

#include <cctype>
#include <iostream>
#include <fstream>
#include <string>

#include "Constants.h"
#include "Game.h"
#include "SDL_error.h"

bool Map::loadMap(const char* path, int sizeX, int sizeY)
{
	std::string tileIDstr;
	char singleChar;
	std::ifstream mapFile;
	mapFile.open(path);

	if (!mapFile.is_open()) {
		SDL_SetError("Error loading map: Couldn't open map file!");
		return false;
	}

	int x = 0, y = 0; // needed outside for-loop for error handling
	bool success = true;
	for (; !mapFile.eof(); mapFile.get(singleChar))
	{
		if (singleChar == ',' || singleChar == '\n') {
			if (tileIDstr.empty())
				continue;
			Game::addTile(std::stoi(tileIDstr), x * TILE_SIZE, y * TILE_SIZE);
			tileIDstr.clear();
			if (singleChar == '\n') {
				if (x != sizeX) {
					SDL_SetError("Error loading map: specified x size doesn't match map file!");
					success = false;
				}
				x = 0;
				y++;
				continue;
			}
			x++;
			continue;
		}
		if (!std::isdigit(singleChar)) continue;
		tileIDstr += singleChar;
	}
	if (y != sizeY) {
		SDL_SetError("Error loading map: specified y size doesn't match map file!");
		success = false;
	}

	mapFile.close();

	return success
}
