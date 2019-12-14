#pragma once

#include "Threads/Thread.h"
#include "Utils/Queue.hpp"

#include <type_traits>
#include <vector>



template <class T, typename D>
class ThreadPool
{
	static_assert(std::is_base_of<Thread, T>::value, "First Template Parameter of ThreadPool Must be a class that inherits Thread Class");

	std::vector<T> _threads;
	std::shared_ptr<Queue<D>> _queue;
	
public:
	ThreadPool(int count)
	{
		for (int i = 0; i < count; ++i) {
			_threads.push_back(T(_queue));
		}
	}

	void Start()
	{
		for (T thread : _queue)
		{
			thread.start();
		}
	}
};