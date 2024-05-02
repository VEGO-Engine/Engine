#include "Game.h"

#include <SDL_error.h>

#include "CollisionHandler.h"
#include "Components.h"
#include "AssetManager.h"
#include "Direction.h"
#include "Entity.h"
#include "HealthComponent.h"
#include "Map.h"
#include "TextureManager.h"
#include "StatEffectsComponent.h"
#include "Constants.h"

Game* engine::game = nullptr; // will be initialized in constructor

Game::Game() :
	manager(this),
	tiles(manager.getGroup((size_t)Entity::GroupLabel::MAPTILES)), 
	players(manager.getGroup((size_t)Entity::GroupLabel::PLAYERS)),
	projectiles(manager.getGroup((size_t)Entity::GroupLabel::PROJECTILE)),
	hearts(manager.getGroup((size_t)Entity::GroupLabel::HEARTS)),
	powerups(manager.getGroup((size_t)Entity::GroupLabel::POWERUPS)),
	player1(manager.addEntity()),
	player2(manager.addEntity()),
	wall(manager.addEntity())
{
	engine::game = this;
};

Game::~Game() = default;

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	Game::assets = new AssetManager(&manager);
	Game::textureManager = new TextureManager(&manager);
	Game::soundManager = new SoundManager();
	Game::collisionHandler = new CollisionHandler(manager); // why does this use a referrence, but AssetManager a pointer?
	
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR. Subsystem couldnt be initialized! " << SDL_GetError() << std::endl;
		SDL_ClearError();
		return;
	}

	if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
		std::cout << "ERROR. Subsystem couldnt be initialized!" << std::endl;
		return;
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (!window)
	{
		std::cout << "ERROR: Window couldnt be created! " << SDL_GetError() << std::endl;
		SDL_ClearError();
		return;
	}

    SDL_Surface* icon = SDL_LoadBMP("assets/iconImage.bmp");
    if(!icon)
    {
        std::cout << "ERROR: Couldn't create icon!" << std::endl;
        return;
    }

    SDL_SetWindowIcon(window, icon);

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		std::cout << "ERROR: Renderer couldnt be created! " << SDL_GetError() << std::endl;
		SDL_ClearError();
		return;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Texture* backgroundTexture = Game::textureManager->loadTexture("assets/startscreen.png");

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "ERROR: Mixer couldnt be initialized! " << SDL_GetError() << std::endl;
		SDL_ClearError();
		return;
	}

	Mix_Volume(-1, MIX_MAX_VOLUME);
	Mix_AllocateChannels(16);

	//SDL_Event event;
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

	engine::init();

	// character selection
	const char* player1Sprite;
	const char* player2Sprite;

	selectCharacters(player1Sprite, player2Sprite);
	if (this->isRunning == false) return;

	map = new Map();


	//adding textures to the library in AssetManager

    /*
    assets->addTexture("player1", "assets/chicken_neutral_knight.png");
    assets->addTexture("player2", "assets/chicken_neutral.png");
    assets->addTexture("egg", "assets/egg.png");
	*/
	// loading sounds
	assets->addSoundEffect("throw_egg", "assets/sound/throw_egg.wav");
	assets->addSoundEffect("steps", "assets/sound/steps.wav");

	//ecs implementation

	player1.setTeam(Entity::TeamLabel::BLUE);
	player1.addComponent<TransformComponent>(80,80,2); //posx, posy, scale
	player1.addComponent<SpriteComponent>(player1Sprite, true); //adds sprite (32x32px), path needed
	player1.addComponent<KeyboardController>(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_E, Vector2D(2, 0));//custom keycontrols can be added
	player1.addComponent<ColliderComponent>("player", 0.8f); //adds tag (for further use, reference tag)
	player1.addComponent<HealthComponent>(5, Direction::LEFT);
	player1.addComponent<StatEffectsComponent>();
	player1.addGroup((size_t) Entity::GroupLabel::PLAYERS); //tell programm what group it belongs to for rendering order


	player2.setTeam(Entity::TeamLabel::RED);
	player2.addComponent<TransformComponent>(600, 500, 2);
	player2.addComponent<SpriteComponent>(player2Sprite, true);
	player2.addComponent<KeyboardController>(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL, Vector2D(-2, 0));
	player2.addComponent<ColliderComponent>("enemy", 0.8f);
	player2.addComponent<HealthComponent>(5, Direction::RIGHT);
	player2.addComponent<StatEffectsComponent>();
	player2.addGroup((size_t) Entity::GroupLabel::PLAYERS);
}

void Game::selectCharacters(const char* &playerSprite, const char* &enemySprite)
{	
	// TODO: move this whereever it makes sense (maybe game as a member)
	std::map<int, std::pair<const char*, const char*>> characterSprites;
	characterSprites[0] = std::make_pair("assets/chicken_neutral_knight.png", "assets/chicken_knight_spritesheet.png");
	characterSprites[1] = std::make_pair("assets/chicken_neutral.png", "assets/chicken_spritesheet.png");
	characterSprites[2] = std::make_pair("assets/chicken_neutral_wizard.png", "assets/chicken_wizard_spritesheet.png");
	characterSprites[3] = std::make_pair("assets/chicken_neutral_mlady.png", "assets/chicken_mlady_spritesheet.png");

	SDL_Rect playerCharacterRects[CHARACTER_COUNT];
	SDL_Rect enemyCharacterRects[CHARACTER_COUNT];
	SDL_Texture* characterTextures[CHARACTER_COUNT];

	int playerSelection = 0;
	int enemySelection = 0;

	// load textures
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		characterTextures[i] = IMG_LoadTexture(renderer, characterSprites.find(i)->second.first);
	}

	// set up initial positions for character rects
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		playerCharacterRects[i] = { 134 + (i % 2) * 118, 272 + ((i >= 2) ? 114 : 0), 64, 64 };
		enemyCharacterRects[i] = { 485 + (i % 2) * 118, 273 + ((i >= 2) ? 114 : 0), 64, 64 };
	}

	bool hasQuit = false;

	while (!hasQuit)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
		{
			hasQuit = true;
		}

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				break;
			}

			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_A:
				playerSelection = (playerSelection - 1 + CHARACTER_COUNT) % CHARACTER_COUNT;
				break;
			case SDL_SCANCODE_D:
				playerSelection = (playerSelection + 1) % CHARACTER_COUNT;
				break;

			case SDL_SCANCODE_LEFT:
				enemySelection = (enemySelection - 1 + CHARACTER_COUNT) % CHARACTER_COUNT;
				break;
			case SDL_SCANCODE_RIGHT:
				enemySelection = (enemySelection + 1) % CHARACTER_COUNT;
				break;

			default:
				break;
			}
		}

		SDL_Texture* backgroundTexture = Game::textureManager->loadTexture("assets/characterSelection.png");
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

		for (int i = 0; i < CHARACTER_COUNT; ++i)
		{
			SDL_RenderCopy(renderer, characterTextures[i], nullptr, &playerCharacterRects[i]);
			SDL_RenderCopy(renderer, characterTextures[i], nullptr, &enemyCharacterRects[i]);
		}

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &playerCharacterRects[playerSelection]);
		SDL_RenderDrawRect(renderer, &enemyCharacterRects[enemySelection]);

		SDL_RenderPresent(renderer);
	}

	if (hasQuit)
	{
		this->isRunning = false;
		return;
	}

	playerSprite = characterSprites.find(playerSelection)->second.second;
	enemySprite = characterSprites.find(enemySelection)->second.second;
	this->isRunning = true;
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
	manager.refresh();
	manager.update();

	engine::update(); // TODO: this might have to be split up into two update functions, before and after manager...
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
		t->draw();

	for (auto& p : powerups)
		p->draw();

	for (auto& p : players)
		p->draw();
	
	for (auto& p : projectiles)
		p->draw();

	for (auto& h : hearts)
		h->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete(textureManager);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}

bool Game::running() const
{
	return isRunning;
}

void Game::setWinner(Entity::TeamLabel winningTeam)
{
	this->winner = winningTeam;
	this->isRunning = false;
}

Entity::TeamLabel Game::getWinner() const
{
	return this->winner;
}

//void Game::refreshPlayers() {
//
//    for(auto& p : projectiles) {
//        p->destroy();
//    }
//
//    player1.getComponent<TransformComponent>().position = Vector2D(80, 80);
//    player2.getComponent<TransformComponent>().position = Vector2D(600, 500);
//
//    player1.getComponent<HealthComponent>().setHealth(5);
//    player2.getComponent<HealthComponent>().setHealth(5);
//
//    isRunning = true;
//
//    update();
//}
