#include "GameInternal.h"

namespace vego {
	extern GameInternal* game;
}

/**
* \brief gives access to internal resources such as managers and handlers
* \details gives access to the following useful managers and handlers
* - this is a list
* - using markdown
* - since markdown is supported :)
*
* 1. also numbered
* 2. lists works
*/
inline GameInternal& VEGO_Game() {
	return *vego::game;
};