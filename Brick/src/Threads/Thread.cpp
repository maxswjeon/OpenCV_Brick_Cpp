#include "Threads/Thread.h"

Thread::Thread()
{
	_status = ThreadStatus::STOPPED;
}

Thread::~Thread()
{
	stop();
}

void Thread::start()
{
	_thread = std::thread(&Thread::run, this);
	_status = ThreadStatus::RUNNING;
}

void Thread::stop()
{
	_status = ThreadStatus::STOPPING;
	_thread.join();
}
