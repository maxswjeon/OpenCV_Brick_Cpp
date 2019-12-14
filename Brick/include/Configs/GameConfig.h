#pragma once

#include "Configs/WindowConfig.h"

struct GameConfig
{
	GameConfig() {}
	
	WindowConfig main_window;
	bool stat_show;
	WindowConfig stat_window;
};
