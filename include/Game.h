#pragma once

#include <cstdint>
#include <optional>
#include <string>

class GameInternal;

// TODO: add managers here
class Game {
public:
    virtual ~Game() {}

    virtual void init() = 0;
    virtual void update(uint_fast16_t diffTime) = 0;

    /*!
     *  \brief Sets the path for a custom config file.
     *
     *  Virtual function to be overwritten in the implementation to return the path of a custom config JSON file.
     *  \sa Layout of the config file is shown in ConfigLoader
     *
     *  \return std::optional<std::string>
     */
    virtual std::optional<std::string> setConfigFilePath() {return std::nullopt;}

    GameInternal* gameInternal; //!< \deprecated  
};


// game factory include to simplify imports in implementation
#include "GameFactory.h"