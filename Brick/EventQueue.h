#pragma once

#include <tbb/concurrent_queue.h>

#include <map>

#include <SDL.h>

class EventQueue
{
private:
	std::map<unsigned int, tbb::concurrent_queue<SDL_Event>> _queues;

	static EventQueue& _instance;

	EventQueue() = default;
	
public:
	void AddQueue(unsigned int windowID);
	void RemoveQueue(unsigned int windowID);
	void Enqueue(SDL_Event e);
	SDL_Event Dequeue(unsigned int windowID);
	int Count() const;

	static EventQueue& GetInstance();

	EventQueue(const EventQueue& other) = delete;
	EventQueue(EventQueue&& other) noexcept = delete;
	EventQueue& operator=(const EventQueue& other) = delete;
	EventQueue& operator=(EventQueue&& other) noexcept = delete;
};

