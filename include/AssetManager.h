#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
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

    void createProjectile(Vector2D pos, Vector2D velocity, int scale, int range, float speed, Textures textureEnum, Entity* owner);
    void createPowerup(Vector2D pos, std::function<void (Entity*)> pickupFunc, Textures texture);

    Vector2D calculateSpawnPosition();
    PowerupType calculateType();


    // sound management
    void addSoundEffect(std::string id, const char* path);
    void addMusic(std::string id, const char* path);

    void addFont(std::string id, const char* path);

    Mix_Chunk* getSound(std::string id); // ??? do we not have a getsound implemented????? too busy to look now, where do we get the soundeffects???
    Mix_Music* getMusic(std::string id);

    TTF_Font* getFont(std::string id);

private:

    Manager* man;
    std::map<std::string, Mix_Chunk*> soundEffects;
    std::map<std::string, Mix_Music*> music;
    std::map<std::string, TTF_Font*> fonts;
};
