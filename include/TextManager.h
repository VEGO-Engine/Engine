#ifndef CHICKENGAME_TEXTMANAGER_H
#define CHICKENGAME_TEXTMANAGER_H

#include <SDL3_ttf/SDL_ttf.h>
#include <map>

class TextManager
{
public:
    TextManager() {}
    ~TextManager() {
        for (auto& it : this->font_cache) {
            TTF_CloseFont(it.second);
        }
    }

    TextManager(TextManager const&) = delete;
    void operator=(TextManager const&) = delete;

    TTF_Font* loadFont(const char* filepath);

    std::map<const char*, TTF_Font*> font_cache;
private:
};

#endif //CHICKENGAME_TEXTMANAGER_H
