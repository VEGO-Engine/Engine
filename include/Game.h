#pragma once

class GameInternal;

// TODO: add managers here
class Game {
public:
    virtual ~Game() {}

    virtual void init() = 0;
    virtual void update() = 0;

    GameInternal* gameInternal; //!< \deprecated  
};


// game factory include to simplify imports in implementation
#include "GameFactory.h"