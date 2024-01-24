#pragma once

#include <map>
#include <SDL_render.h>

#include "AnimationHandler.h"
#include "Component.h"

class TransformComponent;

class SpriteComponent : public Component
{
public:
	int animationIndex = 0;

	std::map<AnimationType, Animation*> animations;

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path);
	SpriteComponent(const char* path, bool isAnimated);
	~SpriteComponent();

	void setTexture(const char* path);

	void init() override;
	void update() override;
	void draw() override;
	void play(AnimationType type);
};
