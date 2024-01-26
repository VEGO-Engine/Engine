#include "KeyboardController.h"

#include "Game.h"
#include "Components.h"
#include "AssetManager.h"

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
	transform->velocity.x = 0;
	transform->velocity.y = 0;
	sprite->play(IDLE);

	if (keystates[this->up]) {
		transform->velocity.y = -1;
		sprite->play(WALK_R);
	}
	if (keystates[this->left]) {
		transform->velocity.x = -1;
		sprite->play(WALK_L);
	}
	if (keystates[this->down]) {
		transform->velocity.y = 1;
		sprite->play(WALK_R);
	}
	if (keystates[this->right]) {
		transform->velocity.x = 1;
		sprite->play(WALK_R);
	}

	if (keystates[this->fire]) {

		Uint32 currentTicks = SDL_GetTicks();

		if (currentTicks - lastFireTime >= fireCooldown) {

			player = &entity->getComponent<TransformComponent>();

			//checks player source via the firing velocity
			//TODO: adding actual projectile textures
			if (fireVelocity.x > 0) {
				Game::assets->createProjectile(Vector2D(player->position.x, player->position.y), fireVelocity,
					false, 1, 180, 1, "assets/egg.png");
			}
			else {
				Game::assets->createProjectile(Vector2D(player->position.x, player->position.y), fireVelocity,
					true, 1, 180, 1, "assets/egg.png");
			}

			lastFireTime = currentTicks;
		}

	}
}