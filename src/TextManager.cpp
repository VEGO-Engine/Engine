#include "TextManager.h"

#include <iostream>

#include "GameInternal.h"
#include "AssetManager.h"

TTF_Font* TextManager::loadFont(const char *filepath)
{
    if(!TTF_Init())
        std::cerr << "Failed to initialize SDL_TTF'" << std::endl;

    auto it = this->font_cache.find(filepath);

    if (it != this->font_cache.end()) {
        return it->second;
    }

    auto font = TTF_OpenFont(filepath, 12); // setting fontsize to 12 for now

    if (font == NULL)
        std::cerr << "Couldn't load font '" << filepath << "'" << std::endl;

    this->font_cache.emplace(filepath, font);

    std::cout << "Loaded font at " << filepath << std::endl;

    return font;
}

SDL_Surface* TextManager::RenderText(GameInternal* game, std::string font, std::string text, DisplayOptions displayOptions, Color fg, Color bg, int wrapWidth)
{
    TTF_Font* ttfFont = game->assets->getFont(font);

    switch(displayOptions)
    {
        case SOLID:
            RenderSolid(font, text, fg, wrapWidth);
            return;
        case SHADED:
            RenderShaded(font, text, fg, bg, wrapWidth);
            return;
        case BLENDED:
            RenderBlended(font, text, fg, wrapWidth)
            return;
        case LCD:
            RenderLCD(font, text, fg, bg, wrapWidth);
            return;
        default:
            std::cerr << "Invalid display option!" << std::endl;
            return;
    }
}

SDL_Surface* TextManager::RenderSolid(TTF_Font* font, std::string text, Color fg, int wrapWidth)
{
    if(wrapWidth == -1)
        return TTF_RenderText_Solid(font, text.c_str(), text.length(), fg);

    return TTF_RenderText_Solid_Wrapped(font, text.c_str(), text.length(), fg, wrapWidth);
}

SDL_Surface* TextManager::RenderShaded(TTF_Font* font, std::string text, Color fg, Color bg, int wrapWidth)
{
    if(wrapWidth == -1)
        return TTF_RenderText_Shaded(font, text.c_str(), text.length(), fg, bg);

    return TTF_RenderText_Shaded_Wrapped(font, text.c_str(), text.length(), fg, bg, wrapWidth);
}

SDL_Surface* TextManager::RenderBlended(TTF_Font* font, std::string text, Color fg, int wrapWidth)
{
    if(wrapWidth == -1)
        return TTF_RenderText_Blended(font, text.c_str(), text.length(), fg);

    return TTF_RenderText_Blended_Wrapped(font, text.c_str(), text.length(), fg, wrapWidth);
}

SDL_Surface* TextManager::RenderLCD(TTF_Font* font, std::string text, Color fg, Color bg, int wrapWidth)
{
    if(wrapWidth == -1)
        return TTF_RenderText_LCD(font, text.c_str(), text.length(), fg, bg);

    return TTF_RenderText_LCD_Wrapped(font, text.c_str(), text.length(), fg, bg, wrapWidth);
}