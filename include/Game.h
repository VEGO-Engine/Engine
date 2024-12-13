#pragma once

class GameInternal;

// TODO: add managers here
class Game {
public:
    virtual ~Game() {}

    virtual void init() = 0;
    virtual void update(uint_fast16_t diffTime) = 0;
    virtual std::optional<std::string> getConfigFilePath() {return std::nullopt;}

    GameInternal* gameInternal; //!< \deprecated  
};


// game factory include to simplify imports in implementation
#include "GameFactory.h"