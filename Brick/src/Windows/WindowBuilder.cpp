#include "Windows/Window.h"

Window::Builder::Builder()
{
	_title = "";
	_x = SDL_WINDOWPOS_UNDEFINED;
	_y = SDL_WINDOWPOS_UNDEFINED;
	_width = 0;
	_height = 0;
	_renderer = 0;
	_wflags = 0;
	_rflags = 0;
}

Window::Builder& Window::Builder::SetTitle(const char* title)
{
	_title = title;
	return *this;
}

Window::Builder& Window::Builder::SetRect(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	return *this;
}

Window::Builder& Window::Builder::SetPosition(int x, int y)
{
	_x = x;
	_y = y;
	return *this;
}

Window::Builder& Window::Builder::SetSize(int width, int height)
{
	_width = width;
	_height = height;
	return *this;
}

Window::Builder& Window::Builder::SetX(int x)
{
	_x = x;
	return *this;
}

Window::Builder& Window::Builder::SetY(int y)
{
	_y = y;
	return *this;
}

Window::Builder& Window::Builder::SetWidth(int width)
{
	_width = width;
	return *this;
}

Window::Builder& Window::Builder::SetHeight(int height)
{
	_height = height;
	return *this;
}

Window::Builder& Window::Builder::SetWindowFlags(int wflags)
{
	_wflags = wflags;
	return *this;
}

Window::Builder& Window::Builder::AddWindowFlag(int flag)
{
	_wflags |= flag;
	return *this;
}

Window::Builder& Window::Builder::DeleteWindowFlag(int flag)
{
	_wflags &= ~flag;
	return *this;
}

Window::Builder& Window::Builder::AddRendererFlag(int flag)
{
	_rflags |= flag;
	return *this;
}

Window::Builder& Window::Builder::DeleteRendererFlag(int flag)
{
	_rflags &= ~flag;
	return *this;
}

Window::Builder& Window::Builder::SetRenderer(int index)
{
	_renderer = index;
	return *this;
}

Window::Builder& Window::Builder::SetRendererFlags(int flags)
{
	_rflags = flags;
	return *this;
}

Window Window::Builder::Build() const
{
	return Window(_title, _x, _y, _width, _height, _renderer, _wflags, _rflags);
}

Window::Window()
{
	_logger = Logger::GetInstance();
	
	_window = nullptr;
	_renderer = nullptr;
}
