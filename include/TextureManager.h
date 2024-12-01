#pragma once

#include "ECS.h"
#include <SDL_render.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "Textures.h"

/*!
 * \class TextureManager
 * \brief A manager for loading, caching, and drawing textures.
 *
 * The `TextureManager` class is responsible for handling texture loading, caching,
 * and rendering in the engine. It provides functions to add, load, and draw textures
 * from files, as well as manage sprite sheets.
 *
 * \sa Textures are used to identify textures within the engine.
 * It is expected that they are implemented within the games scope.
 */

class TextureManager
{
	public:
		TextureManager(Manager* manager) : manager(manager) {}
		~TextureManager() {
			for (auto& it : this->texture_cache) {
				SDL_DestroyTexture(it.second);
			}
			for (auto& it : this->mapTile_texture_cache) {
				SDL_DestroyTexture(it.second);
			}
		}

		/*!
		 * \brief Adds a single texture to the cache.
		 * \param texture The texture identifier.
		 * \param filePath The file path to the texture file.
		 * \throws std::runtime_error Is thrown if the texture could not be loaded correctly
		 *
		 * This function loads the texture from the specified file and stores it in
		 * a cache.
		 */
		void addSingleTexture(Textures texture, const char* filePath);

		/*!
		 * \brief Adds multiple textures to the cache.
		 * \param textures A map of texture identifiers and corresponding file paths.
		 *
		 * This function iterates over the provided map of textures and loads each
		 * texture using `addSingleTexture`. It allows for several
		 * textures to be added at once.
		 */
		void addTextures(const std::map<Textures, const char*>& textures);

		/*!
		 * \brief Loads a texture from the cache.
		 * \param texture The texture identifier.
		 * \return A pointer to the `SDL_Texture` if found, or `nullptr` if not found.
		 *
		 * This function looks up a texture within the cache and returns the
		 * corresponding `SDL_Texture*`. If the texture is not found, it logs an error
		 * message and returns `nullptr`.
		 */
		SDL_Texture* loadTexture(Textures texture);
        static std::vector<SDL_Rect> splitSpriteSheet(SDL_Texture* spriteSheet, int width, int height, int spritesOnSheet);
		static void draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, bool flipped = false);

		/*!
		 * \brief Loads a map tile texture from the file system and caches it.
		 * \param path The file path to the texture.
		 * \return `SDL_Texture*` representing the map tile.
		 * \throws std::runtime_error Is thrown if the texture could not be loaded correctly
		 *
		 * This function checks if the map tile texture is already cached. If not, it
		 * loads the texture from the file system and stores it in the cache.
		 *
		 * \todo should not be usable for the developer and only be accessed by the map class
		 */
		SDL_Texture* loadMapTileTexture(const char* path);

	private:
		Manager* manager;
		std::map<Textures, SDL_Texture*> texture_cache;
		std::map<std::string, SDL_Texture*> mapTile_texture_cache;
};