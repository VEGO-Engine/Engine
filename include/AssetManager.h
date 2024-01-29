#include "Entity.h"

#include <SDL_render.h>
#include <map>
#include <string>

#include "Powerup.h"

class Vector2D;
class Manager;

class AssetManager
{
public:

    AssetManager(Manager* manager);
    ~AssetManager();

    void createProjectile(Vector2D pos, Vector2D velocity, bool source, int scale, int range, int speed, const char* texturePath, TeamLabel teamLabel);
    void createPowerup(Vector2D pos, PowerupType type);

    //texture management
    void addTexture(std::string id, const char* path);

    SDL_Texture* getTexture(std::string id);

private:

    Manager* man;
    std::map<std::string, SDL_Texture*> textures;
};
