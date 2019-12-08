#pragma once

#include <thread>

enum class ThreadStatus
{
	RUNNING,
	STOPPED,
	STOPPING
};

class Thread
{
private:
	std::thread _thread;
	ThreadStatus _status;
	
public:
	Thread();
	virtual ~Thread();

	Thread(const Thread& other) = delete;
	Thread(Thread&& other) noexcept = delete;
	Thread& operator=(const Thread& other) = delete;
	Thread& operator=(Thread&& other) noexcept = delete;
	
	void start();
	void stop();
	virtual void run();

};