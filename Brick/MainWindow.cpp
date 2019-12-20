#include "MainWindow.h"

MainWindow::MainWindow()
	: Window(ConfigLoader::GetString("Game.Window.Name").c_str(),
		ConfigLoader::GetInt("Game.Window.Width"),
		ConfigLoader::GetInt("Game.Window.Height"),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1, 
		SDL_WINDOW_HIDDEN, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
{
	_last_update = std::chrono::system_clock::now();
}

int MainWindow::Render()
{
	//Check Input
	//Status
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(_renderer, 320, 200, 300, 240);
	SDL_RenderDrawLine(_renderer, 300, 240, 340, 240);
	SDL_RenderDrawLine(_renderer, 340, 240, 320, 200);
	SDL_RenderPresent(_renderer);

	SDL_Delay(5);
	return 0;
}


int MainWindow::Loop(SDL_Event e)
{
	return 0;
}