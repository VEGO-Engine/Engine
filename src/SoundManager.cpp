#include "SoundManager.h"

#include <string>
#include <iostream>

#include <SDL3_mixer/SDL_mixer.h>

#include "GameInternal.h"
#include "AssetManager.h"

/*
Mix_Music* SoundManager::loadMusic(const char* fileName)
{
	//auto it = this->music_cache.find(fileName);

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

*/

void SoundManager::playSound(SoundEffects sound, bool canOverlap, int loops, int volume, int channel)
{
	if (!this_instance->sound_cache.contains(sound)) {
		std::cerr << "Error playing Sound-Effect: sound effect not found" << std::endl;
		return;
	}

	if(!canOverlap)
	{
		// dev needs to specify a channel for this check to work, if they set it to -1 and let sdl pick the first available
		// channel mix_getchunk() won't work
		if (Mix_Playing(channel) != 0 && 
			Mix_GetChunk(channel) == this_instance->sound_cache.at(sound) &&
			channel != -1)
		{
			return;
		}
		
		Mix_HaltChannel(channel);
	}

	if(Mix_VolumeChunk(this_instance->sound_cache.at(sound), volume) == -1)
	{
		std::cerr << "Error adjusting volume: " << SDL_GetError() << std::endl;
	}

	if (Mix_PlayChannel(channel, this_instance->sound_cache.at(sound), loops) == -1)
	{
		std::cerr << "Error playing sound " << ": " << SDL_GetError() << std::endl;
	}
}

void SoundManager::playMusic(BackgroundMusic music, int loops, int volume, int milliseconds)
{
	if (!this_instance->music_cache.contains(music)) {
		std::cerr << "Error playing music: music not found" << std::endl;
		return;
	}

	if (Mix_PlayingMusic() != 0 || Mix_Fading() == Mix_Fading::MIX_FADING_IN)
		return;

	if(milliseconds > 0)
	{
		Mix_FadeInMusic(this_instance->music_cache.at(music), loops, milliseconds);
		return;
	}

	if(Mix_VolumeMusic(volume) == -1)
	{
		std::cerr << "Error adjusting volume: " << SDL_GetError() << std::endl;
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

void SoundManager::addSingleSoundEffect(SoundEffects soundEffect, const char *path) {
	if (this_instance->sound_cache.contains(soundEffect)) {
		std::cerr << "Error when adding Sound-Effect: sound-effect with that key already in cache" << std::endl;
		return;
	}

	Mix_Chunk* sound = Mix_LoadWAV(path);

	if (sound == nullptr) {
		std::cerr << "Error when loading Sound-Effect: could not load sound effect from " << path << std::endl;
		return;
	}

	this_instance->sound_cache.emplace(soundEffect, sound);
}

void SoundManager::addSingleBackgroundMusic(BackgroundMusic backgroundMusic, const char *path) {
	if (this_instance->music_cache.contains(backgroundMusic)) {
		std::cerr << "Error when adding Sound-Effect: sound-effect with that key already in cache" << std::endl;
		return;
	}

	Mix_Music* music = Mix_LoadMUS(path);

	if (music == nullptr) {
		std::cerr << "Error when loading Sound-Effect: could not load sound effect from " << path << std::endl;
		return;
	}

	this_instance->music_cache.emplace(backgroundMusic, music);
}

void SoundManager::addSoundEffects(const std::map<SoundEffects, const char *> &effects) {
	for (auto effect : effects)
		addSingleSoundEffect(effect.first, effect.second);
}

void SoundManager::addBackgroundMusic(const std::map<BackgroundMusic, const char *> &backgroundMusic) {
	for (auto track : backgroundMusic)
		addSingleBackgroundMusic(track.first, track.second);
}

SoundManager* SoundManager::this_instance = nullptr;




