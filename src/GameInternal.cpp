#include "GameInternal.h"

#include <SDL_error.h>

#include "CollisionHandler.h"
#include "AssetManager.h"
#include "SoundManager.h"
// #include "KeyboardController.h"
#include "TileComponent.h"
#include "Direction.h"
#include "Entity.h"
#include "HealthComponent.h"
#include "Map.h"
#include "TextureManager.h"
#include "StatEffectsComponent.h"
#include "Constants.h"
#include "Game.h"
#include "GameFactory.h"

GameInternal::GameInternal() :
	manager(this),
	tiles(manager.getGroup((size_t)Entity::GroupLabel::MAPTILES)),
	players(manager.getGroup((size_t)Entity::GroupLabel::PLAYERS)),
	projectiles(manager.getGroup((size_t)Entity::GroupLabel::PROJECTILE)),
	hearts(manager.getGroup((size_t)Entity::GroupLabel::HEARTS)),
	powerups(manager.getGroup((size_t)Entity::GroupLabel::POWERUPS))
	//player1(manager.addEntity()),
	//player2(manager.addEntity())
{};

GameInternal::~GameInternal() = default;

void GameInternal::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	GameInternal::assets = new AssetManager(&manager);
	GameInternal::textureManager = new TextureManager(&manager);
	GameInternal::soundManager = new SoundManager();
	GameInternal::collisionHandler = new CollisionHandler(manager); // why does this use a referrence, but AssetManager a pointer?
	
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

	SDL_Texture* backgroundTexture = GameInternal::textureManager->loadTexture("assets/startscreen.png");

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
		this->setRunning(false);
		return;
	}

	// engine::init(); // temporarily moved down to access groups at engine init call

	// character selection
	//const char* player1Sprite;
	//const char* player2Sprite;

	//selectCharacters(player1Sprite, player2Sprite);
	if (this->isRunning() == false) return;

	map = new Map();

	// loading sounds
	assets->addSoundEffect("throw_egg", "assets/sound/throw_egg.wav");
	assets->addSoundEffect("steps", "assets/sound/steps.wav");

	this->gameInstance = GameFactory::instance().create(this);
	this->gameInstance->init();
}

//void GameInternal::selectCharacters(const char* &playerSprite, const char* &enemySprite)
//{	
//	// TODO: move this whereever it makes sense (maybe game as a member)
//	std::map<int, std::pair<const char*, const char*>> characterSprites;
//	characterSprites[0] = std::make_pair("assets/chicken_neutral_knight.png", "assets/chicken_knight_spritesheet.png");
//	characterSprites[1] = std::make_pair("assets/chicken_neutral.png", "assets/chicken_spritesheet.png");
//	characterSprites[2] = std::make_pair("assets/chicken_neutral_wizard.png", "assets/chicken_wizard_spritesheet.png");
//	characterSprites[3] = std::make_pair("assets/chicken_neutral_mlady.png", "assets/chicken_mlady_spritesheet.png");
//
//	SDL_Rect playerCharacterRects[CHARACTER_COUNT];
//	SDL_Rect enemyCharacterRects[CHARACTER_COUNT];
//	SDL_Texture* characterTextures[CHARACTER_COUNT];
//
//	int playerSelection = 0;
//	int enemySelection = 0;
//
//	// load textures
//	for (int i = 0; i < CHARACTER_COUNT; ++i)
//	{
//		characterTextures[i] = IMG_LoadTexture(renderer, characterSprites.find(i)->second.first);
//	}
//
//	// set up initial positions for character rects
//	for (int i = 0; i < CHARACTER_COUNT; ++i)
//	{
//		playerCharacterRects[i] = { 134 + (i % 2) * 118, 272 + ((i >= 2) ? 114 : 0), 64, 64 };
//		enemyCharacterRects[i] = { 485 + (i % 2) * 118, 273 + ((i >= 2) ? 114 : 0), 64, 64 };
//	}
//
//	bool hasQuit = false;
//
//	while (!hasQuit)
//	{
//		SDL_PollEvent(&event);
//
//		if (event.type == SDL_QUIT)
//		{
//			hasQuit = true;
//		}
//
//		if (event.type == SDL_KEYDOWN)
//		{
//			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
//			{
//				break;
//			}
//
//			switch (event.key.keysym.scancode)
//			{
//			case SDL_SCANCODE_A:
//				playerSelection = (playerSelection - 1 + CHARACTER_COUNT) % CHARACTER_COUNT;
//				break;
//			case SDL_SCANCODE_D:
//				playerSelection = (playerSelection + 1) % CHARACTER_COUNT;
//				break;
//
//			case SDL_SCANCODE_LEFT:
//				enemySelection = (enemySelection - 1 + CHARACTER_COUNT) % CHARACTER_COUNT;
//				break;
//			case SDL_SCANCODE_RIGHT:
//				enemySelection = (enemySelection + 1) % CHARACTER_COUNT;
//				break;
//
//			default:
//				break;
//			}
//		}
//
//		SDL_Texture* backgroundTexture = GameInternal::textureManager->loadTexture("assets/characterSelection.png");
//		SDL_RenderClear(renderer);
//		SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
//
//		for (int i = 0; i < CHARACTER_COUNT; ++i)
//		{
//			SDL_RenderCopy(renderer, characterTextures[i], nullptr, &playerCharacterRects[i]);
//			SDL_RenderCopy(renderer, characterTextures[i], nullptr, &enemyCharacterRects[i]);
//		}
//
//		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//		SDL_RenderDrawRect(renderer, &playerCharacterRects[playerSelection]);
//		SDL_RenderDrawRect(renderer, &enemyCharacterRects[enemySelection]);
//
//		SDL_RenderPresent(renderer);
//	}
//
//	if (hasQuit)
//	{
//		this->setRunning(false);
//		return;
//	}
//
//	playerSprite = characterSprites.find(playerSelection)->second.second;
//	enemySprite = characterSprites.find(enemySelection)->second.second;
//	this->setRunning(true);
//}

void GameInternal::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT: this->setRunning(false);
			break;

		default:
			break;
	}
}

void GameInternal::update()
{
	manager.refresh();
	manager.update();

	this->gameInstance->update(); // TODO: this might have to be split up into two update functions, before and after manager...
}

void GameInternal::render()
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

void GameInternal::clean()
{
	delete(textureManager);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}

bool GameInternal::isRunning() const
{
	return running;
}

void GameInternal::setRunning(bool running) //TODO: might be depracted
{
	this->running = running;
}

void GameInternal::stopGame()
{
	this->running = false;
}
//void GameInternal::setWinner(Entity::TeamLabel winningTeam)
//{
//	this->winner = winningTeam;
//	this->setRunning(false);
//}
//
//Entity::TeamLabel GameInternal::getWinner() const
//{
//	return this->winner;
//}

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
