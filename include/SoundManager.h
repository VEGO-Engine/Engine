#pragma once

#include <SDL_mixer.h>
#include <map>
#include <vector>

#include "ECS.h"
#include "TextureManager.h"
 
// enum SoundTypes
// {
// 	STEPS,
// 	THROW_EGG,
// };

class Game;
class SoundManager
{
	public:
		SoundManager() {}
		~SoundManager() {
			for (auto& it : this->sound_cache) {
				Mix_FreeChunk(it.second);
			}

			for (auto& it : this->music_cache) {
				Mix_FreeMusic(it.second);
			}
		}
		
		SoundManager(SoundManager const&) = delete;
		void operator=(SoundManager const&) = delete;

		std::map<const char*, Mix_Music*> music_cache;
		std::map<const char*, Mix_Chunk*> sound_cache;

		Mix_Music* loadMusic(const char* fileName);
		Mix_Chunk* loadSound(const char* fileName);

		static void playSound(Game* game, std::string sound, bool canOverlap, int loops, int volume);
		static void playMusic(Game* game, std::string sound, int loops, int volume);

		// set general volume
		static void setVolume(int volume);

	private:
};