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

#include "Textures.h"

AssetManager::AssetManager(Manager* manager) : man(manager) {}

AssetManager::~AssetManager() {}

void AssetManager::addSoundEffect(std::string id, const char* path)
{
    soundEffects.emplace(id, this->man->getGame()->soundManager->loadSound(path));
}

void AssetManager::addMusic(std::string id, const char* path)
{
    music.emplace(id, this->man->getGame()->soundManager->loadMusic(path));
}


Mix_Chunk* AssetManager::getSound(std::string id) {
    return soundEffects.at(id);
}

Mix_Music* AssetManager::getMusic(std::string id)
{
	return music.at(id);
}

void AssetManager::createProjectile(Vector2D pos, Vector2D velocity, int scale, int range, int speed, Textures textureEnum, Entity* owner) {

    auto& projectile(man->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, scale); //32x32 is standard size for objects
    projectile.addComponent<SpriteComponent>(textureEnum, 4);
    projectile.addComponent<ProjectileComponent>(range, speed, velocity, owner);
    projectile.addComponent<ColliderComponent>("projectile", 0.6f);
    projectile.addGroup((size_t)Entity::GroupLabel::PROJECTILE);
}

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
		spawnRect.x = rand() % (SCREEN_SIZE_WIDTH - spawnRect.w);
		spawnRect.y = rand() % (SCREEN_SIZE_HEIGHT - spawnRect.h);
		conflict = false;
		for (auto cc : this->man->getGame()->collisionHandler->getColliders({ Entity::GroupLabel::MAPTILES }))
		{
			if (SDL_HasIntersection(&spawnRect, &cc->collider) && strcmp(cc->tag, "projectile"))
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