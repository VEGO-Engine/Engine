#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"
#include "TextureDict.h"

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TextureDict textureDict;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		this->tileRect.x = x;
		this->tileRect.y = y;
		this->tileRect.w = w;
		this->tileRect.h = h;
		tileID = id;

		auto it = textureDict.textureDictionary.find(tileID)->second; //every id has its own distinct texture (in texturedict.h)
		this->path = it;
	}

	~TileComponent() = default;

	void init() override
	{
		this->entity->addComponent<TransformComponent>(this->tileRect.x, this->tileRect.y, this->tileRect.w, this->tileRect.h, 1);
		this->transform = &entity->getComponent<TransformComponent>();

		this->entity->addComponent<SpriteComponent>(this->path);
		this->sprite = &entity->getComponent<SpriteComponent>();
	}
};