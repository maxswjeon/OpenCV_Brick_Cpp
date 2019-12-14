#include "Game.h"



/*
void Game::GetRenderer() const
{	
	_logger->Debug("Get List of Drivers");
	int count = SDL_GetNumRenderDrivers();
	_logger->Debug("%d Drivers Found", count);
	for (int i = 0; i < count; ++i)
	{
		_logger->Debug("Render Driver #%d", i);

		SDL_RendererInfo info;
		memset(&info, 0, sizeof(SDL_RendererInfo));

		int result = SDL_GetRenderDriverInfo(i, &info);
		if (result < 0)
		{
			_logger->Warn("\tFailed to Get Renderer Info");
			continue;
		}
		_logger->Debug("\tName : %s", info.name);
		_logger->Debug("\tRenderer Flags : %d", info.flags);
		_logger->Debug("\tMax Texture Width : %d", info.max_texture_width);
		_logger->Debug("\tMax Texture Height : %d", info.max_texture_height);
		_logger->Debug("\tAvailable Texture Formats :");
		for (unsigned int j = 0; j < info.num_texture_formats; ++j)
		{
			_logger->Debug("\t\tTexture #%d : %d", j, info.texture_formats[j]);
		}
		_logger->Debug(true);
	}
}*/

Game::Game(Window::Builder main_builder) : _main_window(main_builder.Build())
{
	_show_stats = false;
	_queue = std::make_shared<Queue<Frame>>();
	_thread_webcam = WebcamThread(0, _queue);
}

Game::Game(Window::Builder main_builder, Window::Builder stats_builder) : _main_window(main_builder.Build()), _stats_window(stats_builder.Build())
{
	_show_stats = true;
}
