#pragma once

#include <SDL.h>
#include <string>
#include <map>

#include "Component.h"
#include "Textures.h"

class SpriteComponent;
class TransformComponent;

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	Textures texture;

	TileComponent() = default;
	TileComponent(int x, int y, int w, int h, int id, const std::map<int, std::pair<Textures, bool>>* textureDict);
	~TileComponent() = default;

	void init() override;

	bool hasCollision() {
		return this->collision;
	}


private:
	bool collision;
};