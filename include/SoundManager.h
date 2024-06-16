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

/*!
 *
 * \brief Handles music and sound.
 * \details SoundManager handles loading in music and sound effects from files, playing music and sound effects and toggling the audio volume.
 * 
 */
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

		Mix_Music* loadMusic(const char* fileName); //!< Loads music from a file (mp3)
		//! \returns a pointer to Mix_Music, which is added to a map in the AssetManager
		//! \sa AssetManager::AddMusic(std::string id, const char* path)
		Mix_Chunk* loadSound(const char* fileName); //!< Loads sound effects from a file (wav)
		//! \returns a pointer to Mix_Chunk, which is added to a map in the AssetManager
		//! \sa AssetManager::AddSound(std::string id, const char* path)

		static void playSound(Game* game, std::string sound, bool canOverlap, int loops, int volume); //!< Plays sound effects
		//! handles if sounds can overlap, how often they can loop, as well as the volume at which the specified sound effect should play
		static void playMusic(Game* game, std::string sound, int loops, int volume, int ms); //<! Plays music
		//! handles how often the track should loop, as well as the volume at which the specified track should play

		static void setVolume(int volume); //!< Volume handling for the entire program

		static void pauseSound();
		static void pauseMusic();

		static void restartSound();
		static void restartMusic();

		static void fadeOutMusic(int ms);

	private:
};