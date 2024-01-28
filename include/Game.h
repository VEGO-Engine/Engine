#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Vector2D.h"

class AssetManager;
class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() const;

	static void addTile(int id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
    static AssetManager* assets;
    
    bool getWinner();

private:
	int counter = 0;
	bool isRunning = false;
	SDL_Window* window;

    //true for player1 win / false for player2 win;
    bool winner;
};
