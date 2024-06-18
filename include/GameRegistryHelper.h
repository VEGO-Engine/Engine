#pragma once

#include "GameFactory.h"

namespace vego {
	template<typename T>
	class GameRegistryHelper {
	public:
		GameRegistryHelper(const std::string& className) {
			static_assert(std::is_base_of<Game, T>::value, "Your class must inherit from Game");
			GameFactory::instance().registerClass(
				className,
				[]() -> Game* { return new T; }
			);
		};	
	};
}