#pragma once

#include <SDL_mixer.h>
#include <map>
#include <vector>

#include "ECS.h"
#include "TextureManager.h"

enum SoundTypes
{
	STEPS,
	THROW_EGG,
};

class GameInternal;
class SoundManager
{
	public:
		SoundManager() {}
		~SoundManager() {
			for (auto& it : this->sound_cache) {
				Mix_FreeChunk(it.second);
			}
		}
		
		SoundManager(SoundManager const&) = delete;
		void operator=(SoundManager const&) = delete;

		std::map<const char*, Mix_Chunk*> sound_cache;

		Mix_Chunk* loadSound(const char* fileName);
		static void playSound(GameInternal* game, SoundTypes sound);
	private:
};