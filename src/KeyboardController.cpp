#include "KeyboardController.h"

#include "Game.h"
#include "Components.h"
#include "AssetManager.h"
#include "SpriteComponent.h"

KeyboardController::KeyboardController(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, SDL_Scancode fire, Vector2D fireVelocity)
{
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
	this->fire = fire;
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

	if (keystates[this->up]) {
		transform->direction.y = -1;
		sprite->playAnimation(WALK);
	}
	if (keystates[this->left]) {
		transform->direction.x = -1;
		sprite->playAnimation(WALK);
		sprite->setDirection(Direction::LEFT);
	}
	if (keystates[this->down]) {
		transform->direction.y = 1;
		sprite->playAnimation(WALK);
	}
	if (keystates[this->right]) {
		transform->direction.x = 1;
		sprite->playAnimation(WALK);
		sprite->setDirection(Direction::RIGHT);
	}

	if (keystates[this->fire]) {

		Uint32 currentTicks = SDL_GetTicks();

		if (currentTicks - lastFireTime >= fireCooldown) {

			player = &entity->getComponent<TransformComponent>();

			//checks player source via the firing velocity
			//TODO: adding actual projectile textures
			if (fireVelocity.x > 0) {
				sprite->setDirection(Direction::RIGHT);
				Game::assets->createProjectile(Vector2D(player->position.x, player->position.y), fireVelocity,
					false, 1, 180, 2, "assets/egg.png", this->entity->getTeam());
			}
			else {
				sprite->setDirection(Direction::LEFT);
				Game::assets->createProjectile(Vector2D(player->position.x, player->position.y), fireVelocity,
					true, 1, 180, 2, "assets/egg.png", this->entity->getTeam());
			}

			lastFireTime = currentTicks;
		}

	}
}

void KeyboardController::modifyAtkSpeed(int8_t modifier)
{
	this->fireCooldown -= modifier * 400;
}