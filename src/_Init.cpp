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

    return vego::game->init();
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

// triggers upon every event
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    return vego::game->handleEvent(event);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    vego::game->clean();
}