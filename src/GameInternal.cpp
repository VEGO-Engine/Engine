#include "GameInternal.h"

#include "CollisionHandler.h"
#include "AssetManager.h"
#include "RenderManager.h"
#include <SDL3_mixer/SDL_mixer.h>
#include "SDL3/SDL_init.h"
#include "SoundManager.h"
#include "Entity.h"
#include "HealthComponent.h"
#include "Map.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameFactory.h"

#include <VEGO.h>

#include "ConfigLoader.h"

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

SDL_AppResult GameInternal::init()
{
	config = new ConfigLoader();

	this->gameInstance = GameFactory::instance().create(this);
	config->setCustomConfig(this->gameInstance->setConfigFilePath());
	config->init();

	json finalConfig = config->getFinalConfig();

	GameInternal::assets = new AssetManager(&manager);
	GameInternal::textureManager = new TextureManager(&manager);
	GameInternal::soundManager = new SoundManager();
	GameInternal::collisionHandler = new CollisionHandler(manager); // why does this use a referrence, but AssetManager a pointer?
	
	int flags = 0;
	if (finalConfig.at("fullscreen"))
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
	{
		std::cout << "ERROR. Subsystem couldnt be initialized! " << SDL_GetError() << std::endl;
		SDL_ClearError();
		return SDL_APP_FAILURE;
	}

	if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
		std::cout << "ERROR. Subsystem couldnt be initialized!" << std::endl;
		return SDL_APP_FAILURE;
	}

	window = SDL_CreateWindow(finalConfig.at("title").get<std::string>().c_str(),
		finalConfig.at("screen_width"), finalConfig.at("screen_height"), flags);

	if (!window)
	{
		std::cout << "ERROR: Window couldnt be created! " << SDL_GetError() << std::endl;
		SDL_ClearError();
		return SDL_APP_FAILURE;
	}

    // bad
    SDL_Surface* icon;
    if((icon = SDL_LoadBMP(finalConfig.at("icon").get<std::string>().c_str())))
    {
    	SDL_SetWindowIcon(window, icon);
    }

    SDL_SetWindowIcon(window, icon);

	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer)
	{
		std::cout << "ERROR: Renderer couldnt be created! " << SDL_GetError() << std::endl;
		SDL_ClearError();
		return SDL_APP_FAILURE;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	if (!Mix_OpenAudio(0, NULL))
	{
		std::cout << "ERROR: Mixer couldnt be initialized! " << SDL_GetError() << std::endl;
		SDL_ClearError();
		return SDL_APP_FAILURE;
	}

	Mix_Volume(-1, MIX_MAX_VOLUME);
	Mix_AllocateChannels(16);

	// loading sounds
	// assets->addSoundEffect("throw_egg", "assets/sound/throw_egg.wav");
	// assets->addSoundEffect("steps", "assets/sound/steps.wav");

	// loading music
	// assets->addMusic("background_music", "assets/sound/background_music.mp3");

	this->gameInstance->init();

	return SDL_APP_CONTINUE;
}

void GameInternal::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_EVENT_QUIT: this->setRunning(false);
			break;

		default:
			break;
	}
}

void GameInternal::update(Uint64 frameTime)
{
	manager.refresh();

	uint_fast16_t diffTime = frameTime - this->lastFrameTime;
	manager.update(diffTime);

	this->gameInstance->update(diffTime); // TODO: this might have to be split up into two update functions, before and after manager...

	this->lastFrameTime = frameTime;
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

