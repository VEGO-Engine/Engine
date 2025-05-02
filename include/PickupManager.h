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


//! \brief PickupManager class to handle the creation and management of pickups in the game
class PickupManager
{
public:

    PickupManager(Manager* manager);
    ~PickupManager();

    //! \brief Creates a pickupable item and adds it to the manager
    //! \param pos The position of the pickupable item	
    //! \param pickupFunc The function to be called when the pickupable item is picked up
    //! \param texture The texture of the pickupable item
    //! \details This function creates a pickupable item entity and adds it to the manager. The pickupable item is created with a transform component, a sprite component, a collider component and a pickup component. The pickup function is called when the powerup is picked up by an entity.
    void createPickupable(Vector2D pos, std::function<void (Entity*)> pickupFunc, Textures texture);

    Vector2D calculateSpawnPosition();

private:

    Manager* man;
};
