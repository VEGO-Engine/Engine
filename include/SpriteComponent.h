#pragma once

#include <map>
#include <SDL_render.h>
#include <memory>
#include <string>
#include <TextureEnumBase.h>

#include "AnimationHandler.h"
#include "Component.h"
#include "Direction.h"

class TransformComponent;

class SpriteComponent : public Component
{
public:
	int animationIndex = 0;

	std::map<std::string, std::unique_ptr<Animation>>* animations = nullptr;

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	Textures textureEnum;

	bool animated = false;
	uint8_t frames = 0;
	uint8_t speed = 100;
	bool flipped = false;

public:
	SpriteComponent() = default;
	SpriteComponent(Textures textureEnum);
	SpriteComponent(
		Textures textureEnum,
		bool isAnimated,
		std::map<std::string, std::unique_ptr<Animation>>* animationList,
		std::string defaultAnimation);
	~SpriteComponent();

	void setTexture(Textures texture);

	void init() override;
	void update() override;
	void draw() override;
	void playAnimation(std::string type);
	void setDirection(Direction direction);
};
