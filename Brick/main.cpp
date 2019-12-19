#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include "Logger.h"
#include "ConfigLoader.h"
#include "EventHandler.h"

#include "MainWindow.h"
#include "StatsWindow.h"

#include <chrono>

#include <SDL.h>

int InitSDL();

int main(int argc, char* argv[])
{
	if (ConfigLoader::Load(argc, argv) != 0)
	{
		return 1;
	}

	Logger& logger = Logger::GetInstance();
	
	if (InitSDL())
	{
		return 1;
	}

	logger.Debug("Create MainWindow");
	MainWindow main_window;
	/*if (!main_window.Valid)
	{
		logger.Error("Failed to Create Main Window");
	}*/
	//main_window.Show();
	
	SDL_Event e;
	EventHandler& event = EventHandler::GetInstance();
	while (true)
	{
		if (SDL_PollEvent(&e))
		{
			std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
			event.HandleEvent(e);
			std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
			
			std::chrono::milliseconds elapsed = 
				std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			logger.Debug("Event Handle in %lldms", elapsed.count());
			if (elapsed.count() > 5)
			{
				logger.Warn("Event Process Time Exceeded 5ms");
			}

			if (e.type == SDL_QUIT){
				break;
			}
		}
	}

	SDL_Quit();
	return 0;
}

int InitSDL()
{
	Logger& logger = Logger::GetInstance();

	if (const auto error = SDL_Init(SDL_INIT_EVERYTHING))
	{
		logger.Error("Failed to Initialize All Subsystems");
		logger.Error("Error Code %d : %s", error, SDL_GetError());
		return 1;
	}
	logger.Info("Successfully Initialized All SubSystems");
	return 0;
}