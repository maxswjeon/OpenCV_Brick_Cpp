#pragma once
#include "ConfigLoader.h"
#include "Window.h"

class MainWindow : public Window
{
public:
	MainWindow();
protected:
	int Loop(SDL_Event) override;
};

