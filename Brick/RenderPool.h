#pragma once

#include "Logger.h"

#include <chrono>
#include <map>
#include <functional>

class RenderPool
{
	Logger& _logger;
	
	int _renderID = 0;
	std::map<int, std::function<void()>> _render_list;

	RenderPool();
	
public:
	static RenderPool& GetInstance();
	int AddWindow(std::function<void()>);
	void RemoveWindow(int);
	void Render();
	
	RenderPool(const RenderPool& other) = delete;
	RenderPool(RenderPool&& other) noexcept = delete;
	RenderPool& operator=(const RenderPool& other) = delete;
	RenderPool& operator=(RenderPool&& other) noexcept = delete;
};

