#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <cstdint>
#include <functional>
#include <vector>

#include "Manager.h"
#include "Vector2D.h"
#include "Entity.h"
#include "RenderManager.h"
#include "ConfigLoader.h"
#include "PickupManager.h"

typedef std::function<void()> gamefunction;

class CollisionHandler;
class TextureManager;
class SoundManager;
class Map;
class Game;

class GameInternal
{
public:
	GameInternal();
	~GameInternal();

	SDL_AppResult init();

	void handleEvents();
	void update(Uint64 frameTime);
	void render();
	void clean();
	bool isRunning() const;
	void setRunning(bool running); // TODO: should be private/not accesible for game dev
	void stopGame();

	/* static */ SDL_Renderer* renderer = nullptr;
	/* static */ SDL_Event event;
	/* static */ CollisionHandler* collisionHandler;
	/* static */ PickupManager* pickupManager;
    /* static */ TextureManager* textureManager;
    /* static */ SoundManager* soundManager;

    Manager manager;
    RenderManager renderManager;
    Map* map; // game specific, might not be needed for all types of games

	ConfigLoader* config;

	std::vector<Entity*>& tiles;
	std::vector<Entity*>& players;
	std::vector<Entity*>& projectiles;
	std::vector<Entity*>& hearts;
	std::vector<Entity*>& powerups;
	// end moved globals

    void refreshPlayers();

private:

	Game* gameInstance;

	int counter = 0;
	bool running = true;
	SDL_Window* window;

	Uint64 lastFrameTime = 0;
};
