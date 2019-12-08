#include "Utils/Logger.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	Logger* logger = Logger::GetInstance();
	logger->Debug("Initialize Logger Instance");
	
	Game game = Game();
	if (!game.Valid)
	{
		return -1;
	}

	//game.run();
	return 0;
}