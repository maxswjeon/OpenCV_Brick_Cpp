#include "EventQueue.h"

void EventQueue::AddQueue(unsigned int windowID)
{
	if (_queues.count(windowID))
	{
		return;
	}

	_queues.insert(std::make_pair(windowID, tbb::concurrent_queue<SDL_Event>()));
}

void EventQueue::RemoveQueue(unsigned windowID)
{
	if (!_queues.count(windowID))
	{
		return;
	}
	_queues[windowID].clear();
	_queues.erase(windowID);
}

void EventQueue::Enqueue(SDL_Event e)
{
	if (e.type == SDL_WINDOWEVENT) {
		const unsigned int id = e.window.windowID;
		AddQueue(id);
		_queues[id].push(e);
	}
	else
	{
		AddQueue(0);
		_queues[0].push(e);
	}
}

SDL_Event EventQueue::Dequeue(unsigned windowID)
{
	SDL_Event e;
	while (!_queues[windowID].try_pop(e)) {}
	return e;
}

int EventQueue::Count() const
{
	return _queues.size();
}

EventQueue& EventQueue::GetInstance()
{
	static EventQueue _instance;
	return _instance;
}
