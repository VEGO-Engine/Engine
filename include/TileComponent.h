#pragma once
#include "SDL.h"
#include "Component.h"
#include "TextureDict.h"

class SpriteComponent;
class TransformComponent;

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	TextureDict textureDict;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TileComponent() = default;
	TileComponent(int x, int y, int w, int h, int id);
	~TileComponent() = default;

	void init() override;
};