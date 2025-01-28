#ifndef CHICKENGAME_TEXTMANAGER_H
#define CHICKENGAME_TEXTMANAGER_H

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_surface.h>
#include <map>
#include <string>
#include <iostream>

enum DisplayOptions
{
    SOLID,
    SHADED,
    BLENDED,
    LCD,
};

struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

struct Rect
{
    float x;
    float y;
    float w;
    float h;
};

class GameInternal;

class TextManager
{
public:
    TextManager() : font_cache() { }
    ~TextManager() {
        for (auto& it : this->font_cache) {
            TTF_CloseFont(it.second);
        }

        TTF_Quit();
    }

    TextManager(TextManager const&) = delete;
    void operator=(TextManager const&) = delete;

    bool isTextRendered = false;

    TTF_Font* loadFont(const char* filepath);

    // TODO: probably gotta change sdl surface since this is a wrapper func for the dev
    void RenderText(GameInternal* game, std::string font, std::string text, DisplayOptions displayOptions, Color fg, Color bg, int wrapWidth, Rect src, Rect dst);
    void RenderTextFromFile(GameInternal* game, std::string font, std::string filepath, int id, DisplayOptions displayOptions, Color fg, Color bg, int wrapWidth, Rect src, Rect dst);

    std::map<const char*, TTF_Font*> font_cache;

private:
    SDL_Texture* CreateRenderedTexture(GameInternal* game, TTF_Font* font, std::string text, DisplayOptions displayOptions, SDL_Color fg, SDL_Color bg, int wrapWidth);
    SDL_Surface* RenderSolid(TTF_Font* font, std::string text, SDL_Color fg, int wrapWidth);
    SDL_Surface* RenderShaded(TTF_Font* font, std::string text, SDL_Color fg, SDL_Color bg, int wrapWidth);
    SDL_Surface* RenderBlended(TTF_Font* font, std::string text, SDL_Color fg, int wrapWidth);
    SDL_Surface* RenderLCD(TTF_Font* font, std::string text, SDL_Color fg, SDL_Color bg, int wrapWidth);
};

#endif //CHICKENGAME_TEXTMANAGER_H
