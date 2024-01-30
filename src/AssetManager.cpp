#include "AssetManager.h"

#include "Entity.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Components.h"
#include "Game.h"

AssetManager::AssetManager(Manager* manager) : man(manager) {}

AssetManager::~AssetManager() {}

void AssetManager::addTexture(std::string id, const char* path) {
    textures.emplace(id, Game::textureManager->loadTexture(path));
}

void AssetManager::addSoundEffect(std::string id, const char* path)
{
    soundEffects.emplace(id, Game::soundManager->loadSound(path));
}

SDL_Texture* AssetManager::getTexture(std::string id) {
    return textures.at(id);
}

Mix_Chunk* AssetManager::getSound(std::string id) {
    return soundEffects.at(id);
}

void AssetManager::createProjectile(Vector2D pos, Vector2D velocity, int scale, int range, int speed, const char* texturePath, TeamLabel teamLabel) {

    auto& projectile(man->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, scale); //32x32 is standard size for objects
    projectile.addComponent<SpriteComponent>(texturePath);
    projectile.addComponent<ProjectileComponent>(range, speed, velocity);
    projectile.addComponent<ColliderComponent>("projectile", 0.6f);
    projectile.addGroup((size_t)GroupLabel::PROJECTILE);
    projectile.setTeam(teamLabel);
}