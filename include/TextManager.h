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

    /*
     * font - to search for font
     * text - text to display
     * displayoptions - theres like 4 goddamn funcs, ill wrap them all in one
     * fg + bg - solid only takes fg, rest also bg colors
     * wraplength - manually set wraplength, set to 0 to wrap on newline chars, -1 to disable (again. 4 more funcs)
     * */
    // TODO: change the sdl surface, i just dont know what i gotta change it to lol
    SDL_Surface* RenderText(GameInternal* game, std::string font, std::string text, DisplayOptions displayOptions, Color fg, Color bg, int wrapWidth);
    /*
     * takes everything + a filepath to a dialogfile and the id for the dialog
     * */
    SDL_Surface* RenderTextFromFile(GameInternal* game, std::string font, std::string filepath, int id, DisplayOptions displayOptions, Color fg, Color bg, int wrapWidth);

    std::map<const char*, TTF_Font*> font_cache;

private:
    SDL_Surface* RenderSolid(TTF_Font* font, std::string text, SDL_Color fg, int wrapWidth);
    SDL_Surface* RenderShaded(TTF_Font* font, std::string text, SDL_Color fg, SDL_Color bg, int wrapWidth);
    SDL_Surface* RenderBlended(TTF_Font* font, std::string text, SDL_Color fg, int wrapWidth);
    SDL_Surface* RenderLCD(TTF_Font* font, std::string text, SDL_Color fg, SDL_Color bg, int wrapWidth);
};

#endif //CHICKENGAME_TEXTMANAGER_H
