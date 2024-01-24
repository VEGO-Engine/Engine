#include "Game.h"
#include "TextureManager.h"
#include "Manager.h"
#include "Map.h"
#include "Entity.h"
#include "Component.h"
#include "TransformComponent.h"
#include "TileComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "KeyboardController.h"
#include "AssetManager.h"

Map* map;
Manager manager;

AssetManager* Game::assets = new AssetManager(&manager);

SDL_Renderer* Game::renderer = nullptr;

SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& wall(manager.addEntity());
//auto& projectile (manager.addEntity());

Game::Game() = default;

Game::~Game() = default;

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR. Subsystem couldnt be initialized!" << std::endl;
		return;
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (!window)
	{
		std::cout << "ERROR: Window couldnt be created!" << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		std::cout << "ERROR: Renderer couldnt be created!" << std::endl;
		return;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Texture* backgroundTexture = TextureManager::get().loadTexture("assets/startscreen.png");

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	bool hasQuit = false;

	while (!hasQuit)
	{
		SDL_PollEvent(&event);
		
		if (event.type == SDL_QUIT)
		{
			hasQuit = true;
			break;
		}

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				std::cout << "Enter pressed > Game start..." << std::endl;
				break;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				std::cout << "Escape pressed > Game quit..." << std::endl;
				hasQuit = true;
			}
		}
	}

	if (hasQuit)
	{
		this->isRunning = false;
		return;
	}

	this->isRunning = true;

	map = new Map();
	map->loadMap("assets/SDL_map_test.txt", 25, 20);

	//adding textures to the library in AssetManager

    assets->addTexture("player1", "assets/chicken_neutral_knight.png");
    assets->addTexture("player2", "assets/chicken_neutral.png");
    assets->addTexture("egg", "assets/egg.png");


	//ecs implementation

	player.addComponent<TransformComponent>(80,80,2); //posx, posy, scale
	player.addComponent<SpriteComponent>("assets/chicken_knight_spritesheet.png", true); //adds sprite (32x32px), path needed
	player.addComponent<KeyboardController>(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_E, Vector2D(1, 0));//custom keycontrols can be added
	player.addComponent<ColliderComponent>("player"); //adds tag (for further use, reference tag)
	player.addComponent<HealthComponent>(5, &manager, true);
	player.addGroup((size_t)GroupLabel::PLAYERS); //tell programm what group it belongs to for rendering order

	enemy.addComponent<TransformComponent>(600, 500, 2);
	enemy.addComponent<SpriteComponent>("assets/chicken_spritesheet.png", true);
	enemy.addComponent<KeyboardController>(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL, Vector2D(-1, 0));
	enemy.addComponent<ColliderComponent>("enemy");
	enemy.addComponent<HealthComponent>(5, &manager, false);
	enemy.addGroup((size_t)GroupLabel::ENEMIES);

}

auto& tiles(manager.getGroup((size_t)GroupLabel::MAP));
auto& players(manager.getGroup((size_t)GroupLabel::PLAYERS));
auto& enemies(manager.getGroup((size_t)GroupLabel::ENEMIES));
auto& projectiles(manager.getGroup((size_t)GroupLabel::PROJECTILE));
auto& hearts(manager.getGroup((size_t)GroupLabel::HEARTS));

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT: this->isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D enemyPos = enemy.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto cc : colliders)
	{
		if (SDL_HasIntersection(&player.getComponent<ColliderComponent>().collider, &cc->collider) && strcmp(cc->tag, "player") && cc->hasCollision)
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
		if (SDL_HasIntersection(&enemy.getComponent<ColliderComponent>().collider, &cc->collider) && strcmp(cc->tag, "enemy") && cc->hasCollision)
		{
			enemy.getComponent<TransformComponent>().position = enemyPos;
		}
	}

	//checking if projectiles hit player1 or player2
	for (auto& p : projectiles) {
		if(SDL_HasIntersection(&enemy.getComponent<ColliderComponent>().collider, &p->getComponent<ColliderComponent>().collider)
		&& (p->getComponent<ColliderComponent>().hasCollision) && !p->getComponent<ProjectileComponent>().getSource()) {
			//std::cout << "Enemy hit!";
			p->getComponent<ColliderComponent>().removeCollision();
			p->destroy();

			enemy.getComponent<HealthComponent>().getDamage();

			//display updated health | pretty scuffed but works ig
			for(auto h : hearts)
				h->destroy();

			player.getComponent<HealthComponent>().createAllHearts();
			enemy.getComponent<HealthComponent>().createAllHearts();

			if(enemy.getComponent<HealthComponent>().getHealth() < 1) {
				std::cout << "Player1 wins!" << std::endl;
				winner = true;
				isRunning = false;
			}
		}

		if(SDL_HasIntersection(&player.getComponent<ColliderComponent>().collider, &p->getComponent<ColliderComponent>().collider)
		&& (p->getComponent<ColliderComponent>().hasCollision) && p->getComponent<ProjectileComponent>().getSource()) {
			//std::cout << "Player hit!";
			p->getComponent<ColliderComponent>().removeCollision();
			p->destroy();

			player.getComponent<HealthComponent>().getDamage();

			//display updated health
			for(auto h : hearts)
				h->destroy();

			player.getComponent<HealthComponent>().createAllHearts();
			enemy.getComponent<HealthComponent>().createAllHearts();

			if(player.getComponent<HealthComponent>().getHealth() < 1) {
				std::cout << "Player2 wins!" << std::endl;
				winner = false;
				isRunning = false;
			}
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
	for (auto& p : projectiles)
		p->draw();

	for (auto& h : hearts)
		h->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}

void Game::addTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, TILE_SIZE, TILE_SIZE, id);
	if (id == 1) tile.addComponent<ColliderComponent>("water");
	tile.addGroup((size_t)GroupLabel::MAP);
}

bool Game::running() const
{
	return isRunning;
}

bool Game::getWinner() {
	return this->winner;
}