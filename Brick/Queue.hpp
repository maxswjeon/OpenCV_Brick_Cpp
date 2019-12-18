#pragma once
#include <mutex>
#include <queue>

template <typename T>
class Queue
{
private:
	std::condition_variable _cond;
	std::mutex _mutex;
	std::queue<T> _queue;

public:
	void push(const T& data)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_queue.push(data);
		_cond.notify_one();
	}
	
	void push(T&& data)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_queue.push(std::move(data));
		_cond.notify_one();
	}
	
	T pop()
	{
		std::unique_lock<std::mutex> lock(_mutex);
		while (_queue.empty())
		{
			_cond.wait(lock);
		}

		T element = _queue.front();
		_queue.pop();
		return element;
	}
	
	bool empty()
	{
		std::lock_guard<std::mutex> lock(_mutex);
		return _queue.empty();
	}
	
	void clear()
	{
		std::lock_guard<std::mutex> lock(_mutex);
		while(!_queue.empty())
		{
			_queue.pop();
		}
	}
	
	int count()
	{
		std::lock_guard<std::mutex> lock(_mutex);
		return _queue.size();
	}
};

