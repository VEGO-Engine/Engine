#include "SoundManager.h"

#include <stdexcept>
#include <string>
#include <iostream>

#include "Game.h"
#include "AssetManager.h"

Mix_Music* SoundManager::loadMusic(const char* fileName)
{
	auto it = this->music_cache.find(fileName);

	if (it != this->music_cache.end()) {
		return it->second;
	}

	auto music = Mix_LoadMUS(fileName);

	if (music == NULL) 
		throw std::runtime_error(std::string("Couldn't load music '") + fileName + "'");
	
	this->music_cache.emplace(fileName, music);
	
	printf("Loaded music at '%s'\n", fileName);
	
	return music;
}

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

// void SoundManager::playMusic(...)

// TODO: using a string here is probably... a less than stellar method, figure out how to change this
void SoundManager::playSound(Game* game, /*SoundTypes sound*/ std::string sound, bool canOverlap, int loops)
{
	if(!canOverlap)
	{
		if (Mix_Playing(-1) != 0)
			return;
	}

	if (Mix_PlayChannel(-1, game->assets->getSound(sound), loops) == -1) 
	{
		std::cerr << "Error playing sound '" << sound << "': " << Mix_GetError() << std::endl;
	}
}

// TODO:
// functions to 
// 1. free music and sound
// 2. pause/halt music and sound
// 3. restart music and sound
// 4. control volume
