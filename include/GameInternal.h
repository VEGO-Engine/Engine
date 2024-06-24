#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <functional>
#include <vector>

#include "Manager.h"
#include "Vector2D.h"
#include "Entity.h"

typedef std::function<void()> gamefunction;

class AssetManager;
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

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	//void selectCharacters(const char* &playerSprite, const char* &enemySprite);

	void handleEvents();
	void update();
	void render();
	void clean();
	bool isRunning() const;
	void setRunning(bool running); // TODO: should be private/not accesible for game dev
	void stopGame();

	/* static */ SDL_Renderer* renderer = nullptr;
	/* static */ SDL_Event event;
	/* static */ CollisionHandler* collisionHandler;
    /* static */ AssetManager* assets;
    /* static */ TextureManager* textureManager;
    /* static */ SoundManager* soundManager;

    // moved globals
    Manager manager;
    Map* map; // game specific, might not be needed for all types of games

	std::vector<Entity*>& tiles;
	std::vector<Entity*>& players;
	std::vector<Entity*>& projectiles;
	std::vector<Entity*>& hearts;
	std::vector<Entity*>& powerups;
	// end moved globals

    void refreshPlayers();
    //Entity::TeamLabel getWinner() const;
    //void setWinner(Entity::TeamLabel winningTeam);

private:

	Game* gameInstance;

	int counter = 0;
	bool running = true;
	SDL_Window* window;
    //Entity::TeamLabel winner;
};
