#include "SoundManager.h"

#include <stdexcept>
#include <string>
#include <iostream>

#include "Game.h"
#include "AssetManager.h"

Mix_Chunk* SoundManager::loadSound(const char* fileName)
{
	auto it = this->sound_cache.find(fileName);

	if (it != this->sound_cache.end()) {
		return it->second;
	}

	auto sound = Mix_LoadWAV(fileName);

	if (sound == NULL) 
		throw std::runtime_error(std::string("Couldn't load sound '") + fileName + "'");
	
	this->sound_cache.emplace(fileName, sound);
	
	printf("Loaded sound at '%s'\n", fileName);
	
	return sound;
}

void SoundManager::playSound(SoundTypes sound)
{
	switch (sound)
	{
		case SoundTypes::STEPS:
			if (Mix_PlayChannel(-1, Game::assets->getSound("steps"), 0) == -1) {
				std::cerr << "Error playing sound 'steps': " << Mix_GetError() << std::endl;
			}
			break;

		case SoundTypes::THROW_EGG:
			if (Mix_PlayChannel(-1, Game::assets->getSound("throw_egg"), 0) == -1) {
				std::cerr << "Error playing sound 'throw_egg': " << Mix_GetError() << std::endl;
			}
			break;
	}
}
