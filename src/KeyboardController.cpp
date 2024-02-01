#include "KeyboardController.h"

#include "Game.h"
#include "Components.h"
#include "AssetManager.h"
#include "SDL_gamecontroller.h"
#include "SpriteComponent.h"

KeyboardController::KeyboardController(SDL_GameController* gameController, Vector2D fireVelocity)
{
	this->gameController = gameController;
	this->fireVelocity = fireVelocity;
}

void KeyboardController::init()
{
	sprite = &entity->getComponent<SpriteComponent>();
	transform = &entity->getComponent<TransformComponent>();
}

void KeyboardController::update()
{
	transform->direction.x = 0;
	transform->direction.y = 0;
	sprite->playAnimation(IDLE);

	if (SDL_JoystickGetAxis(SDL_GameControllerGetJoystick(this->gameController), 1) < MIN_JOYSTICK_INPUT * -1) { // 
		transform->direction.y = -1;
		sprite->playAnimation(WALK);
		SoundManager::playSound(STEPS);
	}
	if (SDL_JoystickGetAxis(SDL_GameControllerGetJoystick(this->gameController), 0) < MIN_JOYSTICK_INPUT * -1) {
		transform->direction.x = -1;
		sprite->playAnimation(WALK);
		sprite->setDirection(Direction::LEFT);
		SoundManager::playSound(STEPS);
	}
	if (SDL_JoystickGetAxis(SDL_GameControllerGetJoystick(this->gameController), 1) > MIN_JOYSTICK_INPUT) {
		transform->direction.y = 1;
		sprite->playAnimation(WALK);
		SoundManager::playSound(STEPS);
	}
	if (SDL_JoystickGetAxis(SDL_GameControllerGetJoystick(this->gameController), 0) > MIN_JOYSTICK_INPUT) {
		transform->direction.x = 1;
		sprite->playAnimation(WALK);
		sprite->setDirection(Direction::RIGHT);
		SoundManager::playSound(STEPS);
	}

	if (SDL_GameControllerGetButton(this->gameController, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A)) {

		Uint32 currentTicks = SDL_GetTicks();

		if (currentTicks - lastFireTime >= fireCooldown) {

			player = &entity->getComponent<TransformComponent>();

			//checks player source via the firing velocity
			//TODO: adding actual projectile textures
			if (fireVelocity.x > 0) {
				sprite->setDirection(Direction::RIGHT);
				Game::assets->createProjectile(Vector2D(player->position.x, player->position.y), fireVelocity,
					1, 180, 2, "assets/egg.png", this->entity->getTeam());
			}
			else {
				sprite->setDirection(Direction::LEFT);
				Game::assets->createProjectile(Vector2D(player->position.x, player->position.y), fireVelocity,
					1, 180, 2, "assets/egg.png", this->entity->getTeam());
			}

			lastFireTime = currentTicks;
		}
	}
}

void KeyboardController::modifyAtkSpeed(int8_t modifier)
{
	this->fireCooldown -= modifier * 400;
}