#include "EventHandler.h"

EventHandler& EventHandler::GetInstance()
{
	static EventHandler _instance;
	return _instance;
}

void EventHandler::AddWindowHandler(std::function<void(SDL_Event)> listener, unsigned int id)
{
	if (_window_handlers.count(id))
	{
		return;
	}
	_window_handlers.emplace(id, listener);
}

void EventHandler::AddHandler(std::function<void(SDL_Event)> listener, unsigned int type)
{
	if (_handlers.count(type))
	{
		return;
	}
	_handlers.emplace(type, listener);
}

void EventHandler::HandleEvent(SDL_Event event)
{
	if (event.type == SDL_WINDOWEVENT)
	{
		if (!_window_handlers.count(event.window.windowID))
		{
			return;
		}
		_window_handlers[event.window.windowID](event);
	}
	else
	{
		if (!_handlers.count(event.type))
		{
			return;
		}
		_handlers[event.type](event);
	}
}

void EventHandler::RemoveWindowHandler(unsigned int id)
{
	if (!_window_handlers.count(id))
	{
		return;
	}
	_window_handlers.erase(id);
}

