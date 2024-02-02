#include <iostream>
#include <ctime>

#include "Entity.h"
#include "Game.h"
#include "Constants.h"
#include "PopupWindow.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	srand(time(NULL));
    bool playing = true;

	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("No_Name_Chicken_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, false);
    while(playing) {
        while (game->running()) {
            frameStart = SDL_GetTicks();

            game->handleEvents();
            game->update();
            game->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
        Entity::TeamLabel winner = game->getWinner();

        PopupWindow popupWindow("Game over", winner == Entity::TeamLabel::BLUE ?
            "Player1 won! Press 'C' to continue or 'Q' to quit." :
            "Player2 won! Press 'C' to continue or 'Q' to quit.");

        popupWindow.renderWinnerPopup(winner);

        while (!popupWindow.interacted) {
            popupWindow.handleWinnerEvents();
            SDL_Delay(10);
        }
        playing = popupWindow.shouldContinue();
        game->refreshPlayers();
    }

    game->clean();

	return 0;
}