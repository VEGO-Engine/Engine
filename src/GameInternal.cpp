#include "GameInternal.h"

#include <SDL_error.h>

#include "CollisionHandler.h"
#include "AssetManager.h"
#include "RenderManager.h"
#include "SDL_mixer.h"
#include "SoundManager.h"
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
	renderManager(),
	tiles(manager.getGroup((size_t)Entity::GroupLabel::MAPTILES)),
	players(manager.getGroup((size_t)Entity::GroupLabel::PLAYERS)),
	projectiles(manager.getGroup((size_t)Entity::GroupLabel::PROJECTILE)),
	hearts(manager.getGroup((size_t)Entity::GroupLabel::HEARTS)),
	powerups(manager.getGroup((size_t)Entity::GroupLabel::POWERUPS))
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

    // bad
    SDL_Surface* icon;
    if((icon = SDL_LoadBMP("assets/iconImage.bmp")))
    {
    	SDL_SetWindowIcon(window, icon);
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "ERROR: Mixer couldnt be initialized! " << SDL_GetError() << std::endl;
		SDL_ClearError();
		return;
	}

	Mix_Volume(-1, MIX_MAX_VOLUME);
	Mix_AllocateChannels(16);

	// loading sounds
	// assets->addSoundEffect("throw_egg", "assets/sound/throw_egg.wav");
	// assets->addSoundEffect("steps", "assets/sound/steps.wav");

	// loading music
	// assets->addMusic("background_music", "assets/sound/background_music.mp3");

	this->gameInstance = GameFactory::instance().create(this);
	this->gameInstance->init();
}

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
	this->renderManager.renderAll();
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

