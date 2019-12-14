#include "Utils/Logger.h"
#include "Windows/Window.h"
#include "Game.h"

Logger* init_logger();

int main(int argc, char* argv[])
{
	Logger* logger = init_logger();

	Window::Builder mainBuilder = Window::Builder()
		.SetPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)
		.SetSize(1280, 720)
		.SetTitle("OpenCV Brick")
		.AddWindowFlag(SDL_WINDOW_OPENGL)
		.AddWindowFlag(SDL_WINDOW_HIDDEN)
		.SetRenderer(1) //OpenGL is Better than DirectX (Better Pipeline)
		.AddRendererFlag(SDL_RENDERER_ACCELERATED)
		.AddRendererFlag(SDL_RENDERER_PRESENTVSYNC);
	
	Game game = Game(mainBuilder);
	if (!game.Valid)
	{
		return -1;
	}

	//game.run();
	return 0;
}

Logger* init_logger()
{
	Logger* logger = Logger::GetInstance();
	logger->EnableColor();
	logger->SetColor(LogLevel::DEBG, LogColor::WHITE);
	logger->SetColor(LogLevel::VERB, LogColor::BLUE);
	logger->SetColor(LogLevel::INFO, LogColor::GREEN);
	logger->SetColor(LogLevel::WARN, LogColor::YELLOW);
	logger->SetColor(LogLevel::EROR, LogColor::RED);
	logger->Debug("Initialize Logger Instance");
	
	return logger;
}