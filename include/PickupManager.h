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

class PickupManager
{
public:

    PickupManager(Manager* manager);
    ~PickupManager();

    void createPowerup(Vector2D pos, std::function<void (Entity*)> pickupFunc, Textures texture);

    Vector2D calculateSpawnPosition();

private:

    Manager* man;
};
