#include <iostream>
#include <SDL_image.h>

#include "Entity.h"
#include "PopupWindow.h"
#include "TextureManager.h"
#include "GameInternal.h"

/*

PopupWindow::PopupWindow(const char* title, const std::string &message) :
continueGame(false), interacted(false) {
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 250, 0);
    //font = TTF_OpenFont("assets/Trajan.ttf", 24); // Change the path and size as needed

    this->renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);

    //SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), {255, 255, 255});
    //texture = SDL_CreateTextureFromSurface(renderer, surface);

    //SDL_FreeSurface(surface);
}

PopupWindow::~PopupWindow() {
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void PopupWindow::handleWinnerEvents() {

    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            continueGame = false;
            interacted = true;
            return;
        }

        if(e.type != SDL_KEYDOWN)
            continue;

        switch (e.key.keysym.sym) {

            case SDLK_q: {
                continueGame = false;
                interacted = true;
                break;
            }
            case SDLK_c: {
                continueGame =  true;
                interacted = true;
                break;
            }
        }
    }
}

bool PopupWindow::shouldContinue() const {
    return continueGame;
}

void PopupWindow::renderWinnerPopup(Entity::TeamLabel winner) {

    SDL_RenderClear(this->renderer);

    //Maybe use texture manager (changes need to be made that it does not use game::renderer automatically, but receives one instead)
    this->texture = winner == Entity::TeamLabel::BLUE ? 
        IMG_LoadTexture(this->renderer, "assets/Player1Victory.png") :
        IMG_LoadTexture(this->renderer, "assets/Player2Victory.png");

    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);

    SDL_RenderPresent(this->renderer);

    //Error handling for debugging
    const char* sdlError = SDL_GetError();
    if (*sdlError != '\0') {
        std::cerr << "SDL Error: " << sdlError << std::endl;
        SDL_ClearError();
    }

}

*/