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
#include <algorithm>

AssetManager::AssetManager(Manager* manager) : man(manager) {}

AssetManager::~AssetManager() {}

void AssetManager::addTexture(std::string id, const char* path) {
    textures.emplace(id, this->man->getGame()->textureManager->loadTexture(path));
}

void AssetManager::addSoundEffect(std::string id, const char* path)
{
    soundEffects.emplace(id, this->man->getGame()->soundManager->loadSound(path));
}

void AssetManager::addMusic(std::string id, const char* path)
{
    music.emplace(id, this->man->getGame()->soundManager->loadMusic(path));
}

SDL_Texture* AssetManager::getTexture(std::string id) {
    return textures.at(id);
}

Mix_Chunk* AssetManager::getSound(std::string id) {
    return soundEffects.at(id);
}

Mix_Music* AssetManager::getMusic(std::string id)
{
	return music.at(id);
}

void AssetManager::createProjectile(Vector2D pos, Vector2D velocity, int scale, int range, int speed, const char* texturePath, Entity* owner) {

    auto& projectile(man->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, scale); //32x32 is standard size for objects
    projectile.addComponent<SpriteComponent>(texturePath, 4);
    projectile.addComponent<ProjectileComponent>(range, speed, velocity, owner);
    projectile.addComponent<ColliderComponent>("projectile", 0.6f);
    projectile.addGroup((size_t)Entity::GroupLabel::PROJECTILE);
}

void AssetManager::createPowerup(Vector2D pos, std::function<void (Entity*)> pickupFunc, std::string texturePath) {

    auto& powerups(man->addEntity());
    powerups.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1); //32x32 is standard size for objects

    try {
        powerups.addComponent<SpriteComponent>(texturePath.c_str(), 3);
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }

    powerups.addComponent<ColliderComponent>("powerup", 0.6f);
    powerups.addComponent<PowerupComponent>(pickupFunc);
    powerups.addGroup((size_t)Entity::GroupLabel::POWERUPS);
}

Vector2D AssetManager::calculateSpawnPosition(Vector2D size, Vector2D spawnArea)
{
    Vector2D spawnPos = Vector2D(-1, -1);

    for(int i = 0; i <= SPAWN_ATTEMPTS; i++)
    {

        SDL_Rect spawnRect = {
                rand() % (int)(spawnArea.x - size.x),
                rand() % (int)(spawnArea.y - size.y),
                size.x,
                size.y
        };

        std::vector<ColliderComponent*> colliders = this->man->getGame()->collisionHandler->getColliders({Entity::GroupLabel::MAPTILES});
        bool conflict = std::any_of(colliders.begin(), colliders.end(),
                                    [&](const auto& cc) {
                                        return SDL_HasIntersection(&spawnRect, &cc->collider);} );

        if(!conflict)
        {
            spawnPos = Vector2D(spawnRect.x, spawnRect.y);
            break;
        }
    }

    return spawnPos;
}

template <typename T>
T AssetManager::calculateRandomType(int amount)
{
    T type = T(rand() % amount);
    return type;
}
