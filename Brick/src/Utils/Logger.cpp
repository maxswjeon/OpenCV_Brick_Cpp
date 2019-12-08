#include "Utils/Logger.h"

Logger* Logger::_instance = nullptr;

Logger* Logger::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Logger();
	}

	return _instance;
}

Logger::Logger()
{
#if defined(_WIN32) && LOG_COLOR
	DWORD flags;
	GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &flags);
	flags |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), flags);
	
	GetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), &flags);
	flags |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), flags);
#endif
}

void Logger::vLog(LogLevel level, const char* format, va_list ap)
{
	if (level < LOG_LEVEL)
	{
		return;
	}
	
	const char* level_text = "";
	switch (level)
	{
	case LogLevel::DEBG:
		level_text = "DEBG";
		break;
	case LogLevel::VERB:
		level_text = "VERB";
		break;
	case LogLevel::INFO:
		level_text = "INFO";
		break;
	case LogLevel::WARN:
		level_text = "WARN";
		break;
	case LogLevel::EROR:
		level_text = "EROR";
		break;
	}
	
	std::lock_guard<std::mutex> lock(_mutex);
#if LOG_COLOR
	int level_color[] = LOG_COLOR_ARRAY;
	printf("\x1b[%dm", level_color[int(level)]);
#endif
	printf("[%s] ", level_text);
	vprintf(format, ap);
#if LOG_COLOR
	printf("\x1b[0m");
#endif
	printf("\n");
}

void Logger::Log(LogLevel level, std::string format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(level, format.c_str(), ap);
	va_end(ap);
}

void Logger::Log(LogLevel level, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(level, format, ap);
	va_end(ap);
}

void Logger::Debug(std::string format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(LogLevel::DEBG, format.c_str(), ap);
	va_end(ap);
}

void Logger::Debug(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(LogLevel::DEBG, format, ap);
	va_end(ap);
}

void Logger::Debug(bool show_level)
{
	if (LogLevel::DEBG < LOG_LEVEL)
	{
		return;
	}
	
	if (show_level)
	{
		Debug("");
		return;
	}

	std::lock_guard<std::mutex> lock(_mutex);
	printf("\n");
}

void Logger::Verbose(std::string format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(LogLevel::VERB, format.c_str(), ap);
	va_end(ap);
}

void Logger::Verbose(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(LogLevel::VERB, format, ap);
	va_end(ap);
}

void Logger::Verbose(bool show_level)
{
	if (LogLevel::VERB < LOG_LEVEL)
	{
		return;
	}
	
	if (show_level)
	{
		Verbose("");
		return;
	}

	std::lock_guard<std::mutex> lock(_mutex);
	printf("\n");
}

void Logger::Info(std::string format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(LogLevel::INFO, format.c_str(), ap);
	va_end(ap);
}

void Logger::Info(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(LogLevel::INFO, format, ap);
	va_end(ap);
}

void Logger::Info(bool show_level)
{
	if (LogLevel::INFO < LOG_LEVEL)
	{
		return;
	}

	if (show_level)
	{
		Info("");
		return;
	}

	std::lock_guard<std::mutex> lock(_mutex);
	printf("\n");
}

void Logger::Warn(std::string format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(LogLevel::WARN, format.c_str(), ap);
	va_end(ap);
}

void Logger::Warn(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(LogLevel::WARN, format, ap);
	va_end(ap);
}

void Logger::Warn(bool show_level)
{
	if (LogLevel::WARN < LOG_LEVEL)
	{
		return;
	}

	if (show_level)
	{
		Warn("");
		return;
	}

	std::lock_guard<std::mutex> lock(_mutex);
	printf("\n");
}

void Logger::Error(std::string format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(LogLevel::EROR, format.c_str(), ap);
	va_end(ap);
}

void Logger::Error(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	vLog(LogLevel::EROR, format, ap);
	va_end(ap);
}

void Logger::Error(bool show_level)
{
	if (LogLevel::EROR < LOG_LEVEL)
	{
		return;
	}

	if (show_level)
	{
		Error("");
		return;
	}

	std::lock_guard<std::mutex> lock(_mutex);
	printf("\n");
}
