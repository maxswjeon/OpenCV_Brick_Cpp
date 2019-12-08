#include "Game.h"

Game::Game()
{
	_logger = Logger::GetInstance();
	_logger->Verbose("Initialize Logger Instance in Game Instance");

	int result = 0;

	result = InitSdl();
	if (result < 0)
	{
		Valid = false;
		return;
	}

	result = InitWindow();
	if (result < 0)
	{
		Valid = false;
		return;
	}
	
	GetRenderer();

	result = InitRenderer();
	if (result < 0)
	{
		Valid = false;
		return;
	}
	
	Valid = true;
}

int Game::InitSdl() const
{
	int result = 0;
	
	_logger->Verbose("Initialize SDL Library");
	result = SDL_Init(0);
	if (result < 0)
	{
		_logger->Error("Failed to Initialize SDL with No Subsystem");
		_logger->Error("Error Code : %d", result);
		_logger->Error("Error Message : %s", SDL_GetError());
		return result;
	}
	_logger->Verbose("Initialize SDL Library with No Subsystem");

	unsigned int systems[] = {
		SDL_INIT_VIDEO,
		SDL_INIT_AUDIO,
		SDL_INIT_TIMER,
		SDL_INIT_EVENTS
	};

	for (unsigned int system : systems)
	{
		_logger->Verbose("Initialize SDL Subsystem 0x%08x", system);

		result = SDL_InitSubSystem(system);
		if (result < 0)
		{
			_logger->Error("Failed to Initialize SDL Subsystem 0x%08x", system);
			_logger->Error("Error Code : %d", result);
			_logger->Error("Error Message : %s", SDL_GetError());
			return result;
		}
	}
	_logger->Verbose("Successfully Initialized SDL Library");

	return result;
}

int Game::InitWindow()
{
	_logger->Verbose("Creating SDL_Window");
	_window = SDL_CreateWindow(GAME_TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		GAME_WIDTH, GAME_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
	if (_window == NULL)
	{
		_logger->Error("Failed to Create SDL Window");
		_logger->Error("Error Message : %s", SDL_GetError());
		return -1;
	}
	_logger->Verbose("Successfully Initialized SDL Window");
	return 0;
}

void Game::GetRenderer() const
{	
	_logger->Debug("Get List of Drivers");
	int count = SDL_GetNumRenderDrivers();
	_logger->Debug("%d Drivers Found", count);
	for (int i = 0; i < count; ++i)
	{
		_logger->Debug("Render Driver #%d", i);

		SDL_RendererInfo info;
		memset(&info, 0, sizeof(SDL_RendererInfo));

		int result = SDL_GetRenderDriverInfo(i, &info);
		if (result < 0)
		{
			_logger->Warn("\tFailed to Get Renderer Info");
			continue;
		}
		_logger->Debug("\tName : %s", info.name);
		_logger->Debug("\tRenderer Flags : %d", info.flags);
		_logger->Debug("\tMax Texture Width : %d", info.max_texture_width);
		_logger->Debug("\tMax Texture Height : %d", info.max_texture_height);
		_logger->Debug("\tAvailable Texture Formats :");
		for (unsigned int j = 0; j < info.num_texture_formats; ++j)
		{
			_logger->Debug("\t\tTexture #%d : %d", j, info.texture_formats[j]);
		}
		_logger->Debug(true);
	}
}

int Game::InitRenderer()
{
	_logger->Verbose("Config Selected #%d Renderer", GAME_RENDERER);
	_logger->Verbose("Creating SDL Renderer");
	_renderer = SDL_CreateRenderer(_window, GAME_RENDERER, GAME_RENDERER_FLAGS);
	if (_renderer == NULL)
	{
		_logger->Error("Failed to Create SDL Renderer");
		_logger->Error("Error Message : %s", SDL_GetError());
		return -1;
	}
	_logger->Verbose("Successfully Initialized SDL Renderer");
	return 0;
}

