#ifndef SDL_MINIGAME_POPUPWINDOW_H
#define SDL_MINIGAME_POPUPWINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Game;

class PopupWindow {

public:
    PopupWindow(const char* title, const std::string& message);
    ~PopupWindow();

    void handleWinnerEvents();
    bool shouldContinue() const;

    bool interacted;

    void renderWinnerPopup(bool winner);

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* texture;
    bool continueGame;


};



#endif //SDL_MINIGAME_POPUPWINDOW_H
