#include "AssetManager.h"
#include "Component.h"
#include "Components.h"
#include <cstddef>

AssetManager::AssetManager(Manager* manager) : man(manager) {

}

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
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addGroup((size_t)GroupLabel::PROJECTILE);
}