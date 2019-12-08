#pragma once

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "opengl32.lib")

#include "config.h"
#include "Utils/Logger.h"

#include <SDL.h>
#include <SDL_video.h>

class Game
{
private:
	Logger* _logger;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	int InitSdl() const;
	int InitWindow();
	void GetRenderer() const;
	int InitRenderer();
	void InitWebcam();
	
public:
	bool Valid = false;
	
	Game();
	
};