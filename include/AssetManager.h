#pragma once
#include <SDL_render.h>
#include <SDL_mixer.h>
#include <map>
#include <string>
#include <functional>

#include "Entity.h"

class Vector2D;
class Manager;

enum class PowerupType
{
    HEART,
    WALKINGSPEED,
    SHOOTINGSPEED
};

class AssetManager
{
public:

    AssetManager(Manager* manager);
    ~AssetManager();

    void createProjectile(Vector2D pos, Vector2D velocity, int scale, int range, int speed, const char* texturePath, Entity* owner);
    void createPowerup(Vector2D pos, std::function<void (Entity*)> pickupFunc, std::string texturePath);

    Vector2D calculateSpawnPosition(Vector2D size, Vector2D spawnArea);
    template <typename T> [[deprecated]] T calculateRandomType(int amount);

    //texture management
    void addTexture(std::string id, const char* path);

    // sound management
    void addSoundEffect(std::string id, const char* path);

    void addMusic(std::string id, const char* path);

    SDL_Texture* getTexture(std::string id);
    Mix_Chunk* getSound(std::string id);
    Mix_Music* getMusic(std::string id);

private:

    Manager* man;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, Mix_Chunk*> soundEffects;
    std::map<std::string, Mix_Music*> music;
};
