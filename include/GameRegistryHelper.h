#pragma once

#include "GameFactory.h"

namespace vego {
	template<typename T>
	class GameRegistryHelper {
	public:
    	[[deprecated("GameRegistryHelper() does not take a className anymore")]]
		GameRegistryHelper(const std::string& className) {
			static_assert(std::is_base_of<Game, T>::value, "Your class must inherit from Game");
			GameFactory::instance().registerClass(
				[]() -> Game* { return new T; }
			);
		};
		
		GameRegistryHelper() {
			static_assert(std::is_base_of<Game, T>::value, "Your class must inherit from Game");
			GameFactory::instance().registerClass(
				[]() -> Game* { return new T; }
			);
		};	
	};
}