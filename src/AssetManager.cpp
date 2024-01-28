#include "AssetManager.h"

#include "TextureManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* manager) : man(manager) {}

AssetManager::~AssetManager() {}

void AssetManager::addTexture(std::string id, const char* path) {
    textures.emplace(id, TextureManager::get().loadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id) {
    return textures.at(id);
}

void AssetManager::createProjectile(Vector2D pos, Vector2D velocity, bool source, int scale, int range, int speed, const char* texturePath) {

    auto& projectile(man->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, scale); //32x32 is standard size for objects
    projectile.addComponent<SpriteComponent>(texturePath);
    projectile.addComponent<ProjectileComponent>(range, speed, velocity, source);
    projectile.addComponent<ColliderComponent>("projectile", 0.6f);
    projectile.addGroup((size_t)GroupLabel::PROJECTILE);
}

void AssetManager::createPowerup(Vector2D pos, PowerupType type) {
    TextureDict textureDict;

    auto& powerups(man->addEntity());
    powerups.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1); //32x32 is standard size for objects
    auto it = textureDict.powerupDictionary.find(type);
    if (it == textureDict.powerupDictionary.end()) {
        std::cout << "it end" << std::endl;
    }

    try {
        powerups.addComponent<SpriteComponent>(it->second.data());
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }

    powerups.addComponent<ColliderComponent>("powerup", 0.6f);
    powerups.addGroup((size_t)GroupLabel::POWERUPS);
}