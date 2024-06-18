#include <iostream>
#include <ctime>

#include "Entity.h"
#include "GameInternal.h"
#include "Constants.h"
#include "PopupWindow.h"

GameInternal* game = nullptr;

int main(int argc, char* argv[])
{
	srand(time(NULL));
    bool playing = true;

	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new GameInternal();

	game->init("No_Name_Chicken_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, false);
        while (game->isRunning()) {
            frameStart = SDL_GetTicks();

            game->handleEvents();
            game->update();
            game->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }

    game->clean();

	return 0;
}