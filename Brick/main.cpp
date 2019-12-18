#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include "Logger.h"
#include "ConfigLoader.h"

#include "MainWindow.h"

#include <SDL.h>
#include "StatsWindow.h"
#include "EventQueue.h"

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
	MainWindow window;
	if (!window.Valid)
	{
		logger.Error("Failed to Create Main Window");
	}

	window.Show();
	MainWindow window1;
	if (!window1.Valid)
	{
		logger.Error("Failed to Create Main Window");
	}

	window1.Show();

	SDL_Event e;
	EventQueue& queue = EventQueue::GetInstance();
	queue.AddQueue(0);
	while (true)
	{
		if (SDL_PollEvent(&e))
		{
			logger.Debug("Event Polled");
			logger.Debug("\tEvent Type : %d", e.type);
			if (e.type == SDL_WINDOWEVENT)
			{
				logger.Debug("\t Window Event : %d", e.window.event);
				logger.Debug("\t Window ID : %d", e.window.windowID);
			}
			logger.Debug();
			
			if (e.type == SDL_QUIT)
			{
				break;
			}
			
			if (e.type == SDL_WINDOWEVENT) {
				queue.Enqueue(e);
			}
		}
	}
	
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