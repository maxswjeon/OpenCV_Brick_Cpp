#pragma once
#include "EventHandler.h"
#include "Logger.h"

#include "RenderPool.h"

#include <chrono>
#include <SDL.h>

class Window
{
public:
	bool Valid = false;
	bool Focused = false;
	
	Window();
	
	Window(const char* title, 
		int width, int height, 
		int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, 
		int renderer = -1, int wflags = 0, int rflags = SDL_RENDERER_ACCELERATED);

	void Show() const;
	void Hide() const;
		
protected:
	Logger& _logger;

	unsigned int _id;
	int _renderID;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	virtual int Render() = 0;
	virtual int Loop(SDL_Event) = 0;
};

