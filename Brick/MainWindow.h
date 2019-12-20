#pragma once
#include "ConfigLoader.h"
#include "Window.h"

#include <chrono>

class MainWindow : public Window
{
public:
	MainWindow();
protected:
	int Render() override;
	int Loop(SDL_Event) override;

	std::chrono::system_clock::time_point _last_update;
};

