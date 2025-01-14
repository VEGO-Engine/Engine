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
