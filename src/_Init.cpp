#include "SDL3/SDL_init.h"
#include <cstdint>
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include <iostream>
#include <ctime>

#include "VEGO.h"
#include "Entity.h"
#include "GameInternal.h"
#include "Constants.h"

GameInternal* vego::game = nullptr;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    srand(time(NULL));
    bool playing = true;

    *appstate = vego::game = new GameInternal();

    return vego::game->init("No_Name_Chicken_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, false);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    if (!vego::game->isRunning()) {
        return SDL_APP_SUCCESS;
    }

    //vego::game->handleEvents(); // bad

    Uint64 frameStart = SDL_GetTicks();

    vego::game->update(frameStart);
    vego::game->render();

    int frameTime = SDL_GetTicks() - frameStart;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    vego::game->clean();
}