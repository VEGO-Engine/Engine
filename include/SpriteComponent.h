#pragma once

#include <map>
#include <SDL_render.h>
#include <memory>

#include "AnimationHandler.h"
#include "Component.h"
#include "Direction.h"

class TransformComponent;

class SpriteComponent : public Component
{
public:
	int animationIndex = 0;

	std::map<AnimationType, std::unique_ptr<Animation>> animations;

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	uint8_t frames = 0;
	uint8_t speed = 100;
	bool flipped;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path);
	SpriteComponent(const char* path, bool isAnimated);
	~SpriteComponent();

	void setTexture(const char* path);

	void init() override;
	void update() override;
	void draw() override;
	void playAnimation(AnimationType type);
	void setDirection(Direction direction);
};
