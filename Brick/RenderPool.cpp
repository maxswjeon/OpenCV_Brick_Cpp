#include "RenderPool.h"

RenderPool::RenderPool() : _logger(Logger::GetInstance())
{

}

RenderPool& RenderPool::GetInstance()
{
	static RenderPool _instance;
	return _instance;
}

int RenderPool::AddWindow(std::function<void()> fn)
{
	_render_list.emplace(_renderID, fn);
	return _renderID++;
}

void RenderPool::RemoveWindow(int renderID)
{
	_render_list.erase(renderID);
}

void RenderPool::Render()
{
	for (auto pair : _render_list)
	{
		auto start = std::chrono::system_clock::now();
		pair.second();
		auto end = std::chrono::system_clock::now();

		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		_logger.Debug("Render Function #%02d Rendered in %lld ms", pair.first, elapsed.count());
	}
}
