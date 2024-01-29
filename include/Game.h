#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class AssetManager;
class CollisionHandler;
enum class TeamLabel;

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

	static void addTile(unsigned long id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static CollisionHandler* collisionHandler;
    static AssetManager* assets;

private:
    void setWinner(TeamLabel winningTeam);
    TeamLabel getWinner();

	int counter = 0;
	bool isRunning = false;
	SDL_Window* window;
    TeamLabel winner;
};
