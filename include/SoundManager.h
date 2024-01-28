#pragma once

#include <SDL_Mixer.h>
#include <map>
#include <vector>

#include "TextureManager.h"

class SoundManager
{
	public:
		static SoundManager& get()
		{
			static SoundManager instance;
			return instance;
		}

	private:
		SoundManager() {}
		~SoundManager() {
			for (auto& it : this->sound_cache) {
				Mix_FreeChunk(it.second);
			}
		}

	public:
		SoundManager(SoundManager const&) = delete;
		void operator=(SoundManager const&) = delete;

		std::map<const char*, Mix_Chunk*, cmp_str> sound_cache;

		Mix_Chunk* loadSound(const char* fileName);
};