#pragma once

#include "GameFactory.h"

namespace vego {
    template<typename GameType>
    struct GameRegistrar {
        GameRegistrar() {
            static_assert(std::is_base_of<Game, GameType>::value, "Your class must inherit from Game");
            GameFactory::instance().registerClass([]() { return new GameType(); });
        }
    };
}