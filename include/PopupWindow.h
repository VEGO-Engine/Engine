#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Game;
enum class TeamLabel;

class PopupWindow {

public:
    PopupWindow(const char* title, const std::string& message);
    ~PopupWindow();

    void handleWinnerEvents();
    bool shouldContinue() const;

    bool interacted;

    void renderWinnerPopup(TeamLabel winner);

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* texture;
    bool continueGame;
};