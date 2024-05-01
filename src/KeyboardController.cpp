#include "KeyboardController.h"

#include "Game.h"
#include "TransformComponent.h"
#include "AssetManager.h"
#include "SpriteComponent.h"

KeyboardController::KeyboardController(Input* input, Key up, Key down, Key left, Key right, Key fire, Vector2D fireVelocity)
    : m_input(input), m_up(up), m_down(down), m_left(left), m_right(right), m_fire(fire) {}

void KeyboardController::init()
{
	m_sprite = &entity->getComponent<SpriteComponent>();
	m_transform = &entity->getComponent<TransformComponent>();
}

void KeyboardController::update()
{
	m_transform->direction.x = 0;
	m_transform->direction.y = 0;
	m_sprite->playAnimation(IDLE);

	if (m_input->isKeyDown(m_left))
	{
		m_transform->direction.x = -1;
		m_sprite->playAnimation(WALK);
		m_sprite->setDirection(Direction::LEFT);
		SoundManager::playSound(this->entity->getManager().getGame(), STEPS);
	}

	if (m_input->isKeyDown(m_right))
	{
		m_transform->direction.x = 1;
		m_sprite->playAnimation(WALK);
		m_sprite->setDirection(Direction::RIGHT);
		SoundManager::playSound(this->entity->getManager().getGame(), STEPS);
	}

	if (m_input->isKeyDown(m_up))
	{
		m_transform->direction.y = -1;
		m_sprite->playAnimation(WALK);
		SoundManager::playSound(this->entity->getManager().getGame(), STEPS);
	}

	if (m_input->isKeyDown(m_down))
	{
		m_transform->direction.y = 1;
		m_sprite->playAnimation(WALK);
		SoundManager::playSound(this->entity->getManager().getGame(), STEPS);
	}

	if (m_input->isKeyDown(m_fire))
	{
		Uint32 currentTicks = SDL_GetTicks();

		if (currentTicks - m_lastFireTime >= m_fireCooldown)
		{

			m_player = &entity->getComponent<TransformComponent>();

			//checks player source via the firing velocity
			//TODO: adding actual projectile textures
			if (m_fireVelocity.x > 0)
			{
				m_sprite->setDirection(Direction::RIGHT);
				this->entity->getManager().getGame()->assets->createProjectile(Vector2D(m_player->position.x, m_player->position.y), m_fireVelocity,
					1, 180, 2, "assets/egg.png", this->entity->getTeam());
			}

			else
			{
				m_sprite->setDirection(Direction::LEFT);
				this->entity->getManager().getGame()->assets->createProjectile(Vector2D(m_player->position.x, m_player->position.y), m_fireVelocity,
					1, 180, 2, "assets/egg.png", this->entity->getTeam());
			}

			m_lastFireTime = currentTicks;
		}
	}
}

void KeyboardController::modifyAtkSpeed(int8_t modifier)
{
	this->m_fireCooldown -= modifier * 400;
}