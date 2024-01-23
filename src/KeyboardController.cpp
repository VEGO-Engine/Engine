#include "KeyboardController.h"

KeyboardController::KeyboardController()
{

}

KeyboardController::KeyboardController(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right)
{
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
}

KeyboardController::~KeyboardController()
{

}

void KeyboardController::init()
{
	sprite = &entity->getComponent<SpriteComponent>();
	transform = &entity->getComponent<TransformComponent>();
}

void KeyboardController::update()
{
	transform->velocity.x = 0;
	transform->velocity.y = 0;

	if (keystates[this->up]) {
		transform->velocity.y = -1;
		sprite->play(WALK);
	}
	if (keystates[this->left]) {
		transform->velocity.x = -1;
	}
	if (keystates[this->down]) {
		transform->velocity.y = 1;
	}
	if (keystates[this->right]) {
		transform->velocity.x = 1;
	}
}