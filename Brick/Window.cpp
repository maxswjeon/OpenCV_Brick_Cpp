#include "Window.h"

Window::Window() : _logger(Logger::GetInstance())
{
	_window = nullptr;
	_renderer = nullptr;
	_id = 0;
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
	_thread = std::thread([&]
	{
		EventQueue& queue = EventQueue::GetInstance();
		queue.AddQueue(_id);

		SDL_Event e;
		do {
			e = queue.Dequeue(_id);
			if (e.window.event == SDL_WINDOWEVENT_CLOSE || e.type == SDL_QUIT)
			{
				SDL_DestroyWindow(_window);
				Valid = false;
				break;
			}
		}
		while (!Loop(e));

		_logger.Info("Window #%d Closed", _id);
	});
	
	Valid = true;
}

Window::~Window()
{
	_thread.join();
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

void Window::Join()
{
	if (!Valid)
	{
		_logger.Error("Cannot Join an Invalid Window");
		return;
	}

	EventQueue& queue = EventQueue::GetInstance();
	SDL_Event e;
	do
	{
		e = queue.Dequeue(_id);
	} while (Loop(e) == 0);
	queue.RemoveQueue(_id);
}
