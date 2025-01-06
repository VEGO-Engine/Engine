#pragma once

#include "GameInternal.h"

namespace vego {
    extern GameInternal* game;
}

inline GameInternal& VEGO_Game() {
    return *vego::game;
};