#include "Window.h"

Window::Window() : _logger(Logger::GetInstance())
{
	_window = nullptr;
	_renderer = nullptr;
	_id = 0;
}

Window::~Window()
{
	_thread.join();
}

Window::Window(const char* title, int width, int height, int x, int y, int renderer, int wflags, int rflags) : _logger(Logger::GetInstance())
{
	_window = nullptr;
	_renderer = nullptr;
	_id = 0;
	
	_window = SDL_CreateWindow(title, x, y, width, height, wflags);
	if (!_window)
	{
		_logger.Error("Failed to Create Window");
		_logger.Error("%s", SDL_GetError());
		return;
	}

	_renderer = SDL_CreateRenderer(_window, renderer, rflags);
	if (!_renderer)
	{
		_logger.Error("Failed to Create Window");
		_logger.Error("%s", SDL_GetError());
		return;
	}

	_id = SDL_GetWindowID(_window);
	
	EventHandler& event = EventHandler::GetInstance();
	event.AddWindowHandler([&](SDL_Event e) {
		switch (e.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			SDL_DestroyWindow(_window);
			Valid = false;
			
			EventHandler& event = EventHandler::GetInstance();
			event.RemoveWindowHandler(_id);
			
			return;
		}
		Loop(e);
		SDL_Delay(1);
	}, _id);

	_thread = std::thread([&]
		{		
			while (true) {
				auto start = std::chrono::system_clock::now();
				auto target = start + frame_speed(1);

				Update();

				SDL_RenderPresent(_renderer);

				if (std::chrono::system_clock::now() > target)
				{
					_logger.Warn("Frame Refresh Rate Low!");
				}
				else
				{
					std::this_thread::sleep_until(target);
				}
			}
		});
	
	Valid = true;
}

void Window::Show() const
{
	if (!Valid)
	{
		_logger.Error("Cannot Show an Invalid Window");
		return;
	}

	SDL_ShowWindow(_window);
}

void Window::Hide() const
{
	if (!Valid)
	{
		_logger.Error("Cannot Hide an Invalid Window");
		return;
	}

	SDL_HideWindow(_window);
}