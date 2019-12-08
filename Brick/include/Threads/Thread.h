#pragma once

#include <thread>

class Thread
{
private:
	std::thread _thread;

public:
	void start();
	void stop();
};

