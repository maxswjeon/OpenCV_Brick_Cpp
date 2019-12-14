#include "Windows/Window.h"


Window::Window(const char* title, int x, int y, int width, int height, int renderer, int wflags, int rflags)
{
	_logger = Logger::GetInstance();
	_logger->Verbose("Retrieved Logger instance from Window");
	
	// InitSDL
	int result = 0;

	_logger->Verbose("Initialize SDL Library");
	result = SDL_Init(0);
	if (result < 0)
	{
		_logger->Error("Failed to Initialize SDL with No Subsystem");
		_logger->Error("Error Code : %d", result);
		_logger->Error("Error Message : %s", SDL_GetError());
		return;
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

		if (SDL_WasInit(system))
		{
			_logger->Verbose("SDL Subsystem 0x%08x was Initialized Previously", system);
			continue;
		}
		
		result = SDL_InitSubSystem(system);
		if (result < 0)
		{
			_logger->Error("Failed to Initialize SDL Subsystem 0x%08x", system);
			_logger->Error("Error Code : %d", result);
			_logger->Error("Error Message : %s", SDL_GetError());
			return;
		}
	}
	_logger->Verbose("Successfully Initialized SDL Library");
	
	_logger->Verbose("Create Window");
	_logger->Debug("\tWindow Title          : %s", title);
	_logger->Debug("\tWindow Size           : (%d, %d)", width, height);
	_logger->Debug("\tWindow Position       : (%d, %d)", x, y);
	_logger->Debug("\tWindow Creation Flags : 0x%08x", wflags);
	_window = SDL_CreateWindow(title, x, y, width, height, wflags);
	if (!_window)
	{
		_logger->Error("Failed to Create Window");
		return;
	}
	_logger->Verbose("Successfully Created Window");
	
	_logger->Verbose("Create Renderer");
	_logger->Debug("\tRenderer Creation Flags : 0x%08x", rflags);
	_renderer = SDL_CreateRenderer(_window, renderer, rflags);
	if (!_renderer)
	{
		_logger->Error("Failed to Create Renderer");
		return;
	}
	_logger->Verbose("Successfully Created Renderer");

	Valid = true;
}
