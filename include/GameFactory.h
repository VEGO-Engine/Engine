#pragma once

#include <cassert>
#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <stdexcept>

#include "Game.h"

class GameInternal;

class GameFactory {
public:
    using CreateFunc = std::function<Game*()>;

    static GameFactory& instance() {
        static GameFactory factory;
        return factory;
    }

    /*Game* get() {
        assert(this->gameInstance != nullptr);
        return this->gameInstance;
    }*/

    /*Game* create(GameInternal* gameInternal) {
        Game* game = this->gameInstance == nullptr ? this->creator() : this->gameInstance; // TODO: error handling
        game->gameInternal = gameInternal;
        this->gameInstance = game;
        return game;
    }*/

    void registerClass(CreateFunc createFunc) {
        this->creatorFunc = createFunc;
    }

    Game* create(GameInternal* gameInternal) {
        if (this->creatorFunc == nullptr) {
            throw std::runtime_error("No game implementation registered!");
            return nullptr;
        }
        Game* game = (this->creatorFunc)();
        game->gameInternal = gameInternal;
        return game;
    }

private:
    CreateFunc creatorFunc = nullptr;
};

/*
#define REGISTER_GAME(className) \
    static bool registered_##className = []() { \
        GameFactory::instance().registerClass(#className, []() -> Game* { return new className; }); \
        return true; \
    }();
*/
