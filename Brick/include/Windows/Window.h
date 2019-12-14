#pragma once

#include "Utils/Logger.h"

#include <SDL.h>

class Window
{
private:
	Window(const char*, int, int, int, int, int, int, int);

protected:
	Logger* _logger;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

public:
	bool Valid = false;
	
	class Builder
	{
	private:
		const char* _title;
		int _x;
		int _y;
		int _width;
		int _height;
		int _renderer;
		int _wflags;
		int _rflags;
		
	public:
		Builder();
		
		Builder& SetTitle(const char*);
		Builder& SetRect(int, int, int, int);
		Builder& SetPosition(int, int);
		Builder& SetSize(int, int);
		Builder& SetX(int);
		Builder& SetY(int);
		Builder& SetWidth(int);
		Builder& SetHeight(int);
		Builder& SetWindowFlags(int);
		Builder& AddWindowFlag(int);
		Builder& DeleteWindowFlag(int);
		Builder& SetRenderer(int);
		Builder& SetRendererFlags(int);
		Builder& AddRendererFlag(int);
		Builder& DeleteRendererFlag(int);

		Window Build() const;
		
		friend class Window;
	};

	Window();
	virtual ~Window() = default;
};

