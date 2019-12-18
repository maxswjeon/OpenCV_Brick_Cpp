#include "Logger.h"

Logger& Logger::GetInstance()
{
	static Logger _instance;
	return _instance;
}

void Logger::SetLevel(LogLevel level)
{
	_log_level = level;
}

void Logger::EnableColor(bool flag)
{
	_is_color = flag;
	
#ifdef _WIN32
	DWORD flags;
	if (_is_color)
	{
		GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &flags);
		flags |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), flags);

		GetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), &flags);
		flags |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), flags);
	}
	else
	{
		GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &flags);
		flags &= ~ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), flags);

		GetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), &flags);
		flags &= ~ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), flags);
	}
#endif
}

void Logger::SetColor(LogLevel level, LogColor color)
{
	_log_color[int(level)] = color;
}

void Logger::SetColor(LogColor debug, LogColor verbose, LogColor info, LogColor warn, LogColor error)
{
	_log_color[int(LogLevel::DEBG)] = debug;
	_log_color[int(LogLevel::VERB)] = verbose;
	_log_color[int(LogLevel::INFO)] = info;
	_log_color[int(LogLevel::WARN)] = warn;
	_log_color[int(LogLevel::EROR)] = error;
}

LogLevel Logger::GetLevel() const
{
	return _log_level;
}

Logger::Logger() : _log_color{ LogColor::WHITE }
{
	_is_color = false;
	
	//Default Color Set
	SetColor(
		LogColor::WHITE,
		LogColor::BLUE,
		LogColor::GREEN,
		LogColor::YELLOW,
		LogColor::RED);
	
#ifdef _DEBUG
	_log_level = LogLevel::DEBG;
	Debug("_DEBUG was Defined in Compile Time");
	Debug("Log Level fixed to Debug");
#else
	_log_level = LogLevel::INFO;
#endif
}

void Logger::vLog(LogLevel level, const char* format, va_list ap)
{
	if (level < _log_level)
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

	if (_is_color)
	{
		printf("\x1b[%dm", _log_color[int(level)]);
	}
	printf("[%s] ", level_text);
	vprintf(format, ap);
	if (_is_color)
	{
		printf("\x1b[0m");
	}
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
	if (LogLevel::DEBG < _log_level)
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
	if (LogLevel::VERB < _log_level)
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
	if (LogLevel::INFO < _log_level)
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
	if (LogLevel::WARN < _log_level)
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
	if (LogLevel::EROR < _log_level)
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
