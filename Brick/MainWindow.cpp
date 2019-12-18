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
	
}

int MainWindow::Loop(SDL_Event e)
{

	SDL_Delay(1);
	return 0;
}
