#pragma once
#include "EventHandler.h"
#include "Logger.h"

#include <chrono>
#include <thread>
#include <SDL.h>

class Window
{
public:
	bool Valid = false;
	bool Focused = false;
	
	Window();
	virtual ~Window();
	
	Window(const char* title, 
		int width, int height, 
		int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, 
		int renderer = -1, int wflags = 0, int rflags = SDL_RENDERER_ACCELERATED);

	void Show() const;
	void Hide() const;


	
protected:
	Logger& _logger;

	unsigned int _id;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	typedef std::chrono::duration<int, std::ratio<1, 30>> frame_speed;
	std::thread _thread;
	
	virtual int Update() = 0;
	virtual int Loop(SDL_Event) = 0;
};

