#include <SDL_render.h>
#include <SDL_mixer.h>
#include <map>
#include <string>

class Vector2D;
class Manager;

class AssetManager
{
public:

    AssetManager(Manager* manager);
    ~AssetManager();

    void createProjectile(Vector2D pos, Vector2D velocity, bool source, int scale, int range, int speed, const char* texturePath);

    //texture management
    void addTexture(std::string id, const char* path);

    // sound management
    void addSoundEffect(std::string id, const char* path);

    SDL_Texture* getTexture(std::string id);
    Mix_Chunk* getSound(std::string id);

private:

    Manager* man;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, Mix_Chunk*> soundEffects;
};
