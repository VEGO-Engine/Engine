#include "TileComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

TileComponent::TileComponent(int x, int y, int w, int h, int id)
{
	this->tileRect.x = x;
	this->tileRect.y = y;
	this->tileRect.w = w;
	this->tileRect.h = h;
	tileID = id;

	auto it = textureDict.textureDictionary.find(tileID); //every id has its own distinct texture (in texturedict.h)
	if (it == textureDict.textureDictionary.end())
	{
		std::cout << "it end" << std::endl;
		return;
	}
	bool test = it == textureDict.textureDictionary.end();
	// std::cout << it->second.data() << std::endl;
	this->path = it->second.data();
}

void TileComponent::init()
{
	this->entity->addComponent<TransformComponent>(this->tileRect.x, this->tileRect.y, this->tileRect.w, this->tileRect.h, 1);
	this->transform = &entity->getComponent<TransformComponent>();

	this->entity->addComponent<SpriteComponent>(this->path);
	this->sprite = &entity->getComponent<SpriteComponent>();
}

