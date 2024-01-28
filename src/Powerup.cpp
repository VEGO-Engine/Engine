#include "Powerup.h"

#include "TextureDict.h"
#include <SDL.h>
#include "Constants.h"
#include "Game.h"
#include "ColliderComponent.h"

Vector2D Powerup::calculateSpawnPosition()
{
	Vector2D spawnPos = Vector2D(-1,-1);
	bool conflict = false;
	for (int i = 0; i <= SPAWN_ATTEMPTS; i++)
	{
		SDL_Rect spawnRect;
		spawnRect.h = spawnRect.w = 32;
		spawnRect.x = rand() % (SCREEN_SIZE_WIDTH - spawnRect.w);
		spawnRect.y = rand() % (SCREEN_SIZE_HEIGHT - spawnRect.h);
		conflict = false;
		for (auto cc : Game::colliders)
		{
			if (SDL_HasIntersection(&spawnRect, &cc->collider) && strcmp(cc->tag, "projectile"))
			{
				conflict = true;
				break;
			}
		}
		if (conflict) continue;
		spawnPos = Vector2D(spawnRect.x, spawnRect.y);
	}
	return spawnPos;
}

PowerupType Powerup::calculateType()
{
	PowerupType type = PowerupType(rand() % 3);
	return type;
}