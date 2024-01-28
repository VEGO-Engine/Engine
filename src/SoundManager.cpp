#include "SoundManager.h"

#include <stdexcept>
#include <string>

#include "Game.h"

Mix_Chunk* SoundManager::loadSound(const char* fileName)
{
	auto it = this->sound_cache.find(fileName);
	if (it != this->sound_cache.end()) {
		return it->second;
	}
	auto sound = Mix_LoadWAV(fileName);
	if (sound == NULL) throw std::runtime_error(std::string("Couldn't load sound '") + fileName + "'");
	this->sound_cache.emplace(fileName, sound);
	printf("Loaded sound at '%s'\n", fileName);
	return sound;
}