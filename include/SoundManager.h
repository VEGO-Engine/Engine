#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include <map>
#include <vector>

#include "ECS.h"
#include "TextureManager.h"
 
class GameInternal;

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

		/*!
		 * \brief Loads music from a file (mp3)
		 * \returns a pointer to Mix_Music
		 * \sa AssetManager::AddMusic(std::string id, const char* path)
		 */
		Mix_Music* loadMusic(const char* fileName); 
		/*!
		 * \brief Loads sound effects from a file (wav)
		 * \returns a pointer to Mix_Chunk
		 * \sa AssetManager::AddSound(std::string id, const char* path)
		 */
		Mix_Chunk* loadSound(const char* fileName);

		/*!
		 * \brief Handles playing of sound effects
		 *
		 * Handles if sounds can overlap, how often they can loop, as well as the volume at which the specified sound effect should play 
		 * and on which channel the soundeffect should play.
		 */
		static void playSound(GameInternal* game, std::string sound, bool canOverlap, int loops, int volume, int channel);
		/*!
		 * \brief Handles playing of music
		 *
		 * Handles how often track can loop, as well as the volume at which the specified track should play and if it fades in.
		 */
		static void playMusic(GameInternal* game, std::string sound, int loops, int volume, int ms);

		static void setSoundVolume(int volume, int channel); //!< Volume handling for sound effects (either all or on a specific channel)
		static void setMusicVolume(int volume); //!< Volume handling for music track

		static void pauseSound(int channel); //!< Handles pausing sound effects (either all or on a specific channel)
		static void pauseMusic(); //!< Handles pausing music track

		static void restartSound(int channel); //!< Handles resuming sound effects (either all or on a specific channel)
		static void restartMusic(); //!< Handles resuming music track

		static void fadeOutMusic(int ms); //!< Handles fading out a music track

	private:
};