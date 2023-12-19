#pragma once
#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <vector>

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
		bool running();

		static void addTile(int id, int x, int y);
		static SDL_Renderer* renderer;
		static SDL_Event event;
		static std::vector<ColliderComponent*> colliders;

	private:
		int counter = 0;
		bool isRunning = false;
		SDL_Window* window;
};

