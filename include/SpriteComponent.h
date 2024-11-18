#pragma once

#include <map>
#include <SDL3/SDL_render.h>
#include <memory>
#include <string>

#include "AnimationHandler.h"
#include "Component.h"
#include "Direction.h"
#include "RenderObject.h"

class TransformComponent;

class SpriteComponent : public Component, public RenderObject
{
public:
	int animationIndex = 0;

	std::map<std::string, std::unique_ptr<Animation>>* animations = nullptr;

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_FRect srcRect, destRect;

	const char* texturePath;

	bool animated = false;
	uint8_t frames = 0;
	uint8_t speed = 100;
	bool flipped = false;

	int textureXOffset;
	int textureYOffset;

public:
	SpriteComponent(const char* path, int zIndex);
	SpriteComponent(const char* path, int xOffset, int yOffset, int zIndex);
	SpriteComponent(
		const char* path,
		bool isAnimated,
		std::map<std::string, std::unique_ptr<Animation>>* animationList,
		std::string defaultAnimation,
		int zIndex);
	~SpriteComponent();

	void setTexture(const char* path);

	void init() override;
	void update() override;
	void draw() override;
	void playAnimation(std::string type);
	void setDirection(Direction direction);
};
