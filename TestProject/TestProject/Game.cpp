#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& wall(manager.addEntity());

enum GroupLabel
{
	GROUP_MAP,
	GROUP_PLAYERS,
	GROUP_ENEMIES,
	GROUP_COLLIDERS
};

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "ERROR. Subsystem couldnt be initialized!" << std::endl;
		return;
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (!window) {
		std::cout << "ERROR: Window couldnt be created!" << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cout << "ERROR: Renderer couldnt be created!" << std::endl;
		return;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	this->isRunning = true;

	map = new Map();
	map->loadMap("assets/SDL_map_test.txt", 25, 20);

	//ecs implementation

	player.addComponent<TransformComponent>(0,0,2); //posx, posy, scale
	player.addComponent<SpriteComponent>("assets/chicken_neutral_knight.png");
	player.addComponent<KeyboardController>(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D);//custom keycontrols can be added
	player.addComponent<ColliderComponent>("player");
	player.addGroup(GROUP_PLAYERS);

	enemy.addComponent<TransformComponent>(600, 500, 2);
	enemy.addComponent<SpriteComponent>("assets/chicken_neutral.png");
	enemy.addComponent<KeyboardController>(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
	enemy.addComponent<ColliderComponent>("enemy");
	enemy.addGroup(GROUP_ENEMIES);

}

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
		if (SDL_HasIntersection(&player.getComponent<ColliderComponent>().collider, &cc->collider) && strcmp(cc->tag, "player"))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
		if (SDL_HasIntersection(&enemy.getComponent<ColliderComponent>().collider, &cc->collider) && strcmp(cc->tag, "enemy"))
		{
			enemy.getComponent<TransformComponent>().position = enemyPos;
		}
	}

}

auto& tiles(manager.getGroup(GROUP_MAP));
auto& players(manager.getGroup(GROUP_PLAYERS));
auto& enemies(manager.getGroup(GROUP_ENEMIES));

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
	tile.addGroup(GROUP_MAP);
}

bool Game::running()
{
	return isRunning;
}