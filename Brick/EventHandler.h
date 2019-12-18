#pragma once

#include <map>
#include <functional>
#include <chrono>

#include <SDL.h>

class EventHandler
{	
	std::map<unsigned int, std::function<void(SDL_Event)>> _window_handlers;
	std::map<unsigned int, std::function<void(SDL_Event)>> _handlers;

	EventHandler() = default;
	
public:
	static EventHandler& GetInstance();
	
	void AddWindowHandler(std::function<void(SDL_Event)>, unsigned int);
	void AddHandler(std::function<void(SDL_Event)> , unsigned int);
	void RemoveWindowHandler(unsigned int);
	void HandleEvent(SDL_Event);


	EventHandler(const EventHandler& other) = delete;
	EventHandler(EventHandler&& other) noexcept = delete;
	EventHandler& operator=(const EventHandler& other) = delete;
	EventHandler& operator=(EventHandler&& other) noexcept = delete;
};

