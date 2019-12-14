#pragma once
#include <mutex>
#include <queue>

template <typename T>
class Queue
{
private:
	static Queue<T>* _instance;

	std::condition_variable _cond;
	std::mutex _mutex;
	std::queue<T> _queue;
	
public:
	Queue()
	{
		_instance = nullptr;
	}
	
	virtual ~Queue()
	{
		
	}
	
	static Queue<T>* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new Queue();
		}
		return _instance;
	}

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
		std::lock_guard<std::mutex> lock(_mutex);
		while (_queue.empty())
		{
			_cond.wait(lock);
		}
		return _queue.pop();
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

