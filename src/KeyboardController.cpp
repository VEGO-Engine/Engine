#include "KeyboardController.h"
#include "AssetManager.h"

KeyboardController::KeyboardController()
{

}

KeyboardController::KeyboardController(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, SDL_Scancode fire, Vector2D fireVelocity)
{
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
    this->fire = fire;
    this->fireVelocity = fireVelocity;
}

KeyboardController::~KeyboardController()
{

}

void KeyboardController::init()
{
	transform = &entity->getComponent<TransformComponent>();
}

void KeyboardController::update()
{
	transform->velocity.x = 0;
	transform->velocity.y = 0;

	if (keystates[this->up]) {
		transform->velocity.y = -1;
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

    if (keystates[this->fire]) {

        Uint32 currentTicks = SDL_GetTicks();

        if (currentTicks - lastFireTime >= fireCooldown) {

            player = &entity->getComponent<TransformComponent>();

            //checks player source via the firing velocity
            //TODO: adding actual projectile textures
            if(fireVelocity.x > 0) {
                Game::assets->createProjectile(Vector2D(player->position.x, player->position.y), fireVelocity,
                                               false,1, 180, 1, "assets/chicken_neutral_knight.png");
            }
            else {
                Game::assets->createProjectile(Vector2D(player->position.x, player->position.y), fireVelocity,
                                               true,1, 180, 1, "assets/chicken_neutral_knight.png");
            }

            lastFireTime = currentTicks;
        }

    }
}