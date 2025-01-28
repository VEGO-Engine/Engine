#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <map>
#include <string>
#include <functional>

#include "Entity.h"
#include "SoundEffects.h"

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

    void createProjectile(Vector2D pos, Vector2D velocity, int scale, int range, float speed, Textures textureEnum, Entity* owner, SoundEffects soundEffect);
    void createPowerup(Vector2D pos, std::function<void (Entity*)> pickupFunc, Textures texture);

    Vector2D calculateSpawnPosition();
    PowerupType calculateType();


private:

    Manager* man;
};
