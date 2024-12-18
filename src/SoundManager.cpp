#include "SoundManager.h"

#include <stdexcept>
#include <string>
#include <iostream>

#include "GameInternal.h"
#include "AssetManager.h"

Mix_Music* SoundManager::loadMusic(const char* fileName)
{
	auto it = this->music_cache.find(fileName);

	if (it != this->music_cache.end()) {
		return it->second;
	}

	auto music = Mix_LoadMUS(fileName);

	if (music == NULL) 
		std::cerr << "Couldn't load music '" << fileName << "'" << std::endl;
	
	this->music_cache.emplace(fileName, music);
	
	std::cout << "Loaded music at " << fileName << std::endl;
	
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
		std::cerr << "Couldn't load sound '" << fileName << "'" << std::endl;
	
	this->sound_cache.emplace(fileName, sound);
	
	std::cout << "Loaded sound at " << fileName << std::endl;
	
	return sound;
}

void SoundManager::playSound(GameInternal* game, std::string sound, bool canOverlap, int loops, int volume, int channel)
{
	if(!canOverlap)
	{
		// dev needs to specify a channel for this check to work, if they set it to -1 and let sdl pick the first available
		// channel mix_getchunk() won't work
		if (Mix_Playing(channel) != 0 && 
			Mix_GetChunk(channel) == game->assets->getSound(sound) && 
			channel != -1)
		{
			return;
		}
		
		Mix_HaltChannel(channel);
	}

	if(Mix_VolumeChunk(game->assets->getSound(sound), volume) == -1)
	{
		std::cerr << "Error adjusting volume: " << Mix_GetError() << std::endl;
	}

	if (Mix_PlayChannel(channel, game->assets->getSound(sound), loops) == -1) 
	{
		std::cerr << "Error playing sound '" << sound << "': " << Mix_GetError() << std::endl;
	}
}

void SoundManager::playMusic(GameInternal* game, std::string music, int loops, int volume, int ms)
{
	if (Mix_PlayingMusic() != 0 || Mix_Fading() == Mix_Fading::MIX_FADING_IN)
		return;

	if(ms > 0)
	{
		Mix_FadeInMusic(game->assets->getMusic(music), loops, ms);
		return;
	}

	if(Mix_VolumeMusic(volume) == -1)
	{
		std::cerr << "Error adjusting volume: " << Mix_GetError() << std::endl;
	}

	if (Mix_PlayMusic(game->assets->getMusic(music), loops) == -1) 
	{
		std::cerr << "Error playing music '" << music << "': " << Mix_GetError() << std::endl;
	}
}

void SoundManager::setSoundVolume(int volume, int channel)
{
	Mix_Volume(channel, volume);
}

void SoundManager::setMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void SoundManager::pauseSound(int channel)
{
	Mix_Pause(channel);
}

void SoundManager::pauseMusic()
{
	Mix_PauseMusic();
}

void SoundManager::restartSound(int channel)
{
	Mix_Resume(channel);
}

void SoundManager::restartMusic()
{
	Mix_ResumeMusic();
}

void SoundManager::fadeOutMusic(int ms)
{
	if(Mix_Fading() == Mix_Fading::MIX_FADING_OUT)
		return;

	Mix_FadeOutMusic(ms);
}
