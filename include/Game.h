#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>

#include "Manager.h"
#include "Vector2D.h"
#include "Entity.h"

class AssetManager;
class CollisionHandler;
class TextureManager;
class SoundManager;
class Map;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void selectCharacters(const char* &playerSprite, const char* &enemySprite);

	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() const;

	void addTile(unsigned long id, int x, int y);
	/* static */ SDL_Renderer* renderer = nullptr;
	/* static */ SDL_Event event;
	/* static */ CollisionHandler* collisionHandler;
    /* static */ AssetManager* assets;
    /* static */ TextureManager* textureManager;
    /* static */ SoundManager* soundManager;

    // moved globals
    Manager manager;
    Map* map; // game specific, might not be needed for all types of games

    Entity& player1;
	Entity& player2;

	Entity& wall;

	std::vector<Entity*>& tiles;
	std::vector<Entity*>& players;
	std::vector<Entity*>& projectiles;
	std::vector<Entity*>& hearts;
	std::vector<Entity*>& powerups;
	// end moved globals

    void refreshPlayers();
    Entity::TeamLabel getWinner() const;

private:
    void setWinner(Entity::TeamLabel winningTeam);

	int counter = 0;
	bool isRunning = false;
	SDL_Window* window;
    Entity::TeamLabel winner;
};
