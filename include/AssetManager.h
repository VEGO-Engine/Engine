#include <map>
#include <string>

#include "TextureManager.h"
#include "Vector2D.h"
#include "Components.h"
#include "ECS.h"

class AssetManager {

public:

    AssetManager(Manager* manager);
    ~AssetManager();

    void createProjectile(Vector2D pos, Vector2D velocity, bool source, int scale, int range, int speed, const char* texturePath);

    //texture management
    void addTexture(std::string id, const char* path);

    SDL_Texture* getTexture(std::string id);

private:

    Manager* man;
    std::map<std::string, SDL_Texture*> textures;
};
