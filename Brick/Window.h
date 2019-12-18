#pragma once
#include "EventQueue.h"
#include "Logger.h"

#include <thread>

#include <SDL.h>

class Window
{
public:
	bool Valid = false;
	
	Window();
	virtual ~Window();
	
	Window(const char* title, 
		int width, int height, 
		int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, 
		int renderer = -1, int wflags = SDL_WINDOW_HIDDEN, int rflags = SDL_RENDERER_ACCELERATED);

	void Show() const;
	void Hide() const;
	void Join();

	
protected:
	Logger& _logger;
	
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::thread _thread;

	unsigned int _id;
	
	virtual int Loop(SDL_Event) = 0;
};

