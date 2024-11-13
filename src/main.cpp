#include <iostream>
#include <ctime>

#include "VEGO.h"
#include "Entity.h"
#include "GameInternal.h"
#include "Constants.h"

GameInternal* vego::game = nullptr;

int main(int argc, char* argv[])
{
	srand(time(NULL));
    bool playing = true;

	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	vego::game = new GameInternal();

	vego::game->init("No_Name_Chicken_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, false);
        while (vego::game->isRunning()) {
            frameStart = SDL_GetTicks();

            vego::game->handleEvents();
            vego::game->update();
            vego::game->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }

    vego::game->clean();

	return 0;
}