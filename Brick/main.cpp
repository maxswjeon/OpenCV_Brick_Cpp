#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include "Logger.h"
#include "ConfigLoader.h"
#include "EventHandler.h"
#include "RenderPool.h"
#include "FrameHandler.h"

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
	if (!main_window.Valid)
	{
		logger.Error("Failed to Create Main Window");
	}
	
	SDL_Event e;
	EventHandler& event = EventHandler::GetInstance();
	RenderPool& render = RenderPool::GetInstance();
	FrameHandler handler = FrameHandler(0, 8);
	if (handler.Start())
	{
		return 3;
	}

	main_window.Show();
	
	while (true)
	{
		logger.Debug("Loop Start");
		
		auto time_start = std::chrono::system_clock::now();
		std::chrono::milliseconds elapsed;
		
		if (SDL_PollEvent(&e))
		{
			event.HandleEvent(e);
			if (e.type == SDL_QUIT){
				break;
			}
		}
		auto time_event = std::chrono::system_clock::now();
		
		render.Render();
		auto time_render = std::chrono::system_clock::now();

		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time_event - time_start);
		//logger.Debug("Event Handled in %lld ms", elapsed.count());
		if (elapsed.count() > 5)
		{
			logger.Warn("Event Process Time Exceeded 5ms");
		}
		
		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time_render - time_event);
		//logger.Debug("Rendered in %lld ms", elapsed.count());
		if (elapsed.count() > 20)
		{
			logger.Warn("Render Time Exceeded 20ms");
		}

		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time_render - time_start);
		if (elapsed.count() > 1000 / 30)
		{
			logger.Warn("Frame Drop Occured");			
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