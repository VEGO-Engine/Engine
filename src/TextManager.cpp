#include "TextManager.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include "GameInternal.h"
#include "AssetManager.h"

using json = nlohmann::json;

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

void TextManager::RenderText(GameInternal* game, std::string font, std::string text, DisplayOptions displayOptions, Color fg, Color bg, int wrapWidth, Rect src, Rect dst)
{
    TTF_Font* ttfFont = game->assets->getFont(font);
    SDL_Color sdlFg = {fg.r, fg.g, fg.b, fg.a};
    SDL_Color sdlBg = {bg.r, bg.g, bg.b, bg.a};

    SDL_FRect sdlSrcRect = { src.x, src.y, src.w, src.h };
    SDL_FRect sdlDstRect = { dst.x, dst.y, dst.w, dst.h };

    SDL_RenderTexture(VEGO_Game().renderer, CreateRenderedTexture(ttfFont, text, displayOptions, sdlFg, sdlBg, wrapWidth), &sdlSrcRect, &sdlDstRect);
}

void TextManager::RenderTextFromFile(GameInternal* game, std::string font, std::string filepath, int id, DisplayOptions displayOptions, Color fg, Color bg, int wrapWidth, Rect src, Rect dst)
{
    TTF_Font* ttfFont = game->assets->getFont(font);
    SDL_Color sdlFg = {fg.r, fg.g, fg.b, fg.a};
    SDL_Color sdlBg = {bg.r, bg.g, bg.b, bg.a};

    SDL_FRect sdlSrcRect = { src.x, src.y, src.w, src.h };
    SDL_FRect sdlDstRect = { dst.x, dst.y, dst.w, dst.h };

    std::ifstream f(filepath);
    json data = json::parse(f);;

    auto it = std::find_if(data.begin(), data.end(), [id](const nlohmann::json& obj){
        return obj.contains("id") && obj["id"]  == id;
    });

    if(it == data.end() || !it->contains("line"))
        std::cerr << "Object with id " << id << " not found or 'line' not present!" << std::endl;

    std::string text = (*it)["line"];

    SDL_RenderTexture(VEGO_Game().renderer, CreateRenderedTexture(ttfFont, text, displayOptions, sdlFg, sdlBg, wrapWidth), &sdlSrcRect, &sdlDstRect);
}

SDL_Texture* TextManager::CreateRenderedTexture(TTF_Font* font, std::string text, DisplayOptions displayOptions, SDL_Color fg, SDL_Color bg, int wrapWidth)
{
    SDL_Surface* surface = nullptr;

    switch(displayOptions)
    {
        case SOLID:
            surface = RenderSolid(font, text, fg, wrapWidth);
            break;
        case SHADED:
            surface = RenderShaded(font, text, fg, bg, wrapWidth);
            break;
        case BLENDED:
            surface = RenderBlended(font, text, fg, wrapWidth);
            break;
        case LCD:
            surface = RenderLCD(font, text, fg, bg, wrapWidth);
            break;
        default:
            std::cerr << "Invalid display option!" << std::endl;
            break;
    }

    if(!surface)
        std::cerr << "Error when rendering text!" << std::endl;

    return SDL_CreateTextureFromSurface(VEGO_Game().renderer, surface);
}

SDL_Surface* TextManager::RenderSolid(TTF_Font* font, std::string text, SDL_Color fg, int wrapWidth)
{
    if(wrapWidth == -1)
        return TTF_RenderText_Solid(font, text.c_str(), text.length(), fg);

    return TTF_RenderText_Solid_Wrapped(font, text.c_str(), text.length(), fg, wrapWidth);
}

SDL_Surface* TextManager::RenderShaded(TTF_Font* font, std::string text, SDL_Color fg, SDL_Color bg, int wrapWidth)
{
    if(wrapWidth == -1)
        return TTF_RenderText_Shaded(font, text.c_str(), text.length(), fg, bg);

    return TTF_RenderText_Shaded_Wrapped(font, text.c_str(), text.length(), fg, bg, wrapWidth);
}

SDL_Surface* TextManager::RenderBlended(TTF_Font* font, std::string text, SDL_Color fg, int wrapWidth)
{
    if(wrapWidth == -1)
        return TTF_RenderText_Blended(font, text.c_str(), text.length(), fg);

    return TTF_RenderText_Blended_Wrapped(font, text.c_str(), text.length(), fg, wrapWidth);
}

SDL_Surface* TextManager::RenderLCD(TTF_Font* font, std::string text, SDL_Color fg, SDL_Color bg, int wrapWidth)
{
    if(wrapWidth == -1)
        return TTF_RenderText_LCD(font, text.c_str(), text.length(), fg, bg);

    return TTF_RenderText_LCD_Wrapped(font, text.c_str(), text.length(), fg, bg, wrapWidth);
}