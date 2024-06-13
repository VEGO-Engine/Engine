#pragma once

#include <cassert>
#include <iostream>
#include <map>
#include <functional>
#include <string>

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

    void registerClass(const std::string& className, CreateFunc createFunc) {
        this->creators[className] = createFunc;
    }

    Game* create(const std::string& className, GameInternal* gameInternal) {
        auto it = this->creators.find(className);
        if (it != creators.end()) {
            Game* game = it->second();
            game->gameInternal = gameInternal;
            return game;
        }
        return nullptr;
    }

private:
    CreateFunc creator;
    std::map<std::string, CreateFunc> creators;
};

/*
#define REGISTER_GAME(className) \
    static bool registered_##className = []() { \
        GameFactory::instance().registerClass(#className, []() -> Game* { return new className; }); \
        return true; \
    }();
*/
