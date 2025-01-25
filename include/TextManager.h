#ifndef CHICKENGAME_TEXTMANAGER_H
#define CHICKENGAME_TEXTMANAGER_H

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_surface.h>
#include <map>
#include <string>

enum DisplayOptions
{
    SOLID,
    SHADED,
    BLENDED,
    LCD,
};

struct Color
{
    int r;
    int g;
    int b;
    int a;
};

class GameInternal;

class TextManager
{
public:
    TextManager() {}
    ~TextManager() {
        for (auto& it : this->font_cache) {
            TTF_CloseFont(it.second);
        }

        TTF_Quit();
    }

    TextManager(TextManager const&) = delete;
    void operator=(TextManager const&) = delete;

    TTF_Font* loadFont(const char* filepath);

    // TODO: probably gotta change sdl surface since this is a wrapper func for the dev
    SDL_Surface* RenderText(GameInternal* game, std::string font, std::string text, DisplayOptions displayOptions, Color fg, Color bg, int wrapWidth);
    SDL_Surface* RenderTextFromFile(GameInternal* game, std::string font, std::string filepath, int id, DisplayOptions displayOptions, Color fg, Color bg, int wrapWidth);

    std::map<const char*, TTF_Font*> font_cache;

private:
    SDL_Surface* RenderSolid(TTF_Font* font, std::string text, SDL_Color fg, int wrapWidth);
    SDL_Surface* RenderShaded(TTF_Font* font, std::string text, SDL_Color fg, SDL_Color bg, int wrapWidth);
    SDL_Surface* RenderBlended(TTF_Font* font, std::string text, SDL_Color fg, int wrapWidth);
    SDL_Surface* RenderLCD(TTF_Font* font, std::string text, SDL_Color fg, SDL_Color bg, int wrapWidth);
};

#endif //CHICKENGAME_TEXTMANAGER_H
