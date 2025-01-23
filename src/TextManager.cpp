#include "TextManager.h"

#include <iostream>

TTF_Font* TextManager::loadFont(const char *filepath)
{
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