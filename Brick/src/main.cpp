#include "Utils/Logger.h"

int main(int argc, char* argv[])
{
	Logger* logger = Logger::GetInstance();
	logger->Debug("Initialize Logger Instance");
	return 0;
}