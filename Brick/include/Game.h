#pragma once

#pragma comment(lib, "opencv_world412.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "opengl32.lib")

#include "Utils/Logger.h"
#include "Windows/MainWindow.h"
#include "Windows/StatsWindow.h"
#include "Threads/WebcamThread.h"

#include <SDL.h>
#include <SDL_video.h>

class Game
{
private:
	Logger* _logger;

	MainWindow _main_window;
	StatsWindow _stats_window;

	std::shared_ptr<Queue<Frame>> _queue;
	WebcamThread _thread_webcam;

	bool _show_stats;
		
public:
	bool Valid = false;

	Game(Window::Builder main_builder);
	Game(Window::Builder main_builder, Window::Builder stats_builder);
	
};
