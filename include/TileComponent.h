#pragma once

#include <SDL.h>
#include <string>
#include <map>

#include "Component.h"

class SpriteComponent;
class TransformComponent;

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TileComponent() = default;
	TileComponent(int x, int y, int w, int h, int id, const std::map<int, std::pair<std::string, bool>>* textureDict);
	~TileComponent() = default;

	void init() override;

	bool hasCollision(){return this->collision;}
	std::string getName(){return this->tileName;}

	std::string componentName() override { return "TileComponent"; }
	
private:
	bool collision;
	std::string tileName;
};