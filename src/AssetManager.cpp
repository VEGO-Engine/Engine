#include "AssetManager.h"

#include "TextureManager.h"
#include "SoundManager.h"
#include "ProjectileComponent.h"
#include "GameInternal.h"

#include "TransformComponent.h"

#include "CollisionHandler.h"
#include "ColliderComponent.h"
#include "Constants.h"
#include "Entity.h"
#include "Vector2D.h"
#include "PowerupComponent.h"
#include <iostream>
#include <VEGO.h>

#include "Textures.h"

AssetManager::AssetManager(Manager* manager) : man(manager) {}

AssetManager::~AssetManager() {}

void AssetManager::createPowerup(Vector2D pos, std::function<void (Entity*)> pickupFunc, Textures texture) {

    auto& powerups(man->addEntity());
    powerups.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1); //32x32 is standard size for objects

    try {
        powerups.addComponent<SpriteComponent>(texture, 3);
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }

    powerups.addComponent<ColliderComponent>("powerup", 0.6f);
    powerups.addComponent<PowerupComponent>(pickupFunc);
    powerups.addGroup((size_t)Entity::GroupLabel::POWERUPS);
}

Vector2D AssetManager::calculateSpawnPosition()
{
	Vector2D spawnPos = Vector2D(-1, -1);
	bool conflict = false;
	for (int i = 0; i <= SPAWN_ATTEMPTS; i++)
	{
		SDL_Rect spawnRect;
		spawnRect.h = spawnRect.w = 32;
		spawnRect.x = rand() % (VEGO_Game().config->getFinalConfig().at("screen_width").get<int>() - spawnRect.w);
		spawnRect.y = rand() % (VEGO_Game().config->getFinalConfig().at("screen_height").get<int>() - spawnRect.h);
		conflict = false;
		for (auto cc : this->man->getGame()->collisionHandler->getColliders({ Entity::GroupLabel::MAPTILES }))
		{
			if (SDL_HasRectIntersection(&spawnRect, &cc->collider) && strcmp(cc->tag, "projectile"))
			{
				conflict = true;
				break;
			}
		}
		if (conflict) continue;
		spawnPos = Vector2D(spawnRect.x, spawnRect.y);
	}
	return spawnPos;
}

PowerupType AssetManager::calculateType()
{
	PowerupType type = PowerupType(rand() % 3);
	return type;
}