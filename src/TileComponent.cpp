#include "TileComponent.h"

#include <iostream>

#include "Entity.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"


TileComponent::TileComponent(int x, int y, int w, int h, int id, const std::map<int, std::pair<Textures, bool>>* textureDict)
{
	this->tileRect.x = x;
	this->tileRect.y = y;
	this->tileRect.w = w;
	this->tileRect.h = h;
	tileID = id;

	auto it = textureDict->find(tileID); //every id has its own distinct texture (in texturedict.h)
	if (it == textureDict->end()) {
		std::cout << "it end" << std::endl;
		return;
	}
	
	this->collision = it->second.second;
	this->texture = it->second.first;
}

void TileComponent::init()
{
	this->entity->addComponent<TransformComponent>(this->tileRect.x, this->tileRect.y, this->tileRect.w, this->tileRect.h, 1);
	this->transform = &entity->getComponent<TransformComponent>();

	this->entity->addComponent<SpriteComponent>(this->texture, 0);
	this->sprite = &entity->getComponent<SpriteComponent>();
}

