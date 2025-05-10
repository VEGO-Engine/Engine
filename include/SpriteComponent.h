#pragma once

#include <map>
#include <SDL3/SDL_render.h>
#include <memory>
#include <string>

#include "Textures.h"
#include "AnimationHandler.h"
#include "Component.h"
#include "Direction.h"
#include "RenderObject.h"

class TransformComponent;

//! \brief SpriteComponent class to handle sprite rendering and animation of entities
class SpriteComponent : public Component, public RenderObject
{
public:
	int animationIndex = 0;

	std::map<std::string, std::unique_ptr<Animation>>* animations = nullptr;

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_FRect srcRect, destRect;

	Textures textureEnum;

	bool animated = false;
	uint8_t frames = 0;
	uint8_t speed = 100;
	bool flipped = false;

	int textureXOffset;
	int textureYOffset;

	//there should be a better solution as this variable is only used for the loading of the tmx map
	//TODO: improve this in the future and also remove it from the scope of the developer
	const char* path; //!< empty string if texture has a texture enum value, otherwise the path of the texture

public:
    //debug
    Textures getTexture() { return this->textureEnum; }

	//! \param texture The texture to be used for the sprite, must be a Texture enum
	//! \param xOffset The x offset of the sprite relative to the transform component position, used for rendering position 
	//! \param yOffset The y offset of the sprite relative to the transform component position, used for rendering position
	//! \param zIndex The z-index of the sprite, used for rendering order, in order to show up on the map, the zIndex must be higher than the layer you want it to show up on
	SpriteComponent(Textures texture, int zIndex, int xOffset = 0, int yOffset = 0);

	//! \param path The path to the texture to be used for the entity (for performance reasons, prefer enums instead)
	//! \param xOffset The x offset of the sprite relative to the transform component position, used for rendering position
	//! \param yOffset The y offset of the sprite relative to the transform component position, used for rendering position
	//! \param zIndex The z-index of the sprite, used for rendering order, in order to show up on the map, the zIndex must be higher than the layer you want it to show up on
	SpriteComponent(const char* path, int zIndex, int xOffset = 0, int yOffset = 0);

	/**
	 *  \brief Constructor used for **animated** sprites
	 *  \param texture The texture to be used for the sprite, must be a Texture enum
	 *  \param isAnimated Whether the sprite is animated or not
	 *  \param animationList The list of animations to be used for the sprite (list of maps mapping a string to an \ref Animation struct)
	 *  \param defaultAnimation The default animation to be used for the sprite when it first gets loaded
	 *  \param zIndex The z-index of the sprite, used for rendering order, in order to show up on the map, the zIndex must be higher than the layer you want it to show up on
	 *  \param xOffset The x offset of the sprite relative to the transform component position, used for rendering position
	 *  \param yOffset The y offset of the sprite relative to the transform component position, used for rendering position
	 *  ### How to spritesheet animation:
	 * 
	 * An animation sprite sheet consists of multiple sprites of the specified size (library supports 32x32) arranged in a grid.
	 * Each row of the grid represents one animation, and each column in a row is one frame of the animation.
	 * If a sprite sheet contains multiple animations with different frame counts,
	 * you can just leave the rest of the row blank.
	 * Be aware to specify the correct frame count in the animation struct!
	 * \sa Animation
	 * 
	 * \image html Animations1.jpg "Example of a sprite sheet with 2 animations of 2 frames each"
	*/
	 SpriteComponent(
		Textures texture,
		bool isAnimated,
		std::map<std::string, std::unique_ptr<Animation>>* animationList,
		std::string defaultAnimation,
		int zIndex,
		int xOffset = 0,
		int yOffset = 0);

	~SpriteComponent();

	void setTexture(Textures texture);
	void setMapTileTexture(const char* path);

	void init() override;
	void update(uint_fast16_t diffTime) override;
	void draw() override;

	//! \brief By name select which animation should be played (gets looped)
	//! \param type name previously set to an animation in animationList
	void playAnimation(std::string type);
	void setDirection(Direction direction);
};
