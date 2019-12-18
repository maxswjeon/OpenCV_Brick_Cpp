#pragma once

#if defined(_WIN32)
#include <Windows.h>
#endif

#include <string>
#include <mutex>

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

enum class LogColor : char {
	BLACK = 30,
	RED = 31,
	GREEN = 32,
	YELLOW = 33,
	BLUE = 34,
	MAGENTA = 35,
	CYAN = 36,
	WHITE = 37
};

enum class LogLevel :int
{
	DEBG = 0,
	VERB,
	INFO,
	WARN,
	EROR
};

class Logger
{
private:
	std::mutex _mutex;
	static Logger _instance;

	bool _is_color;
	LogColor _log_color[5];
	LogLevel _log_level;
	

	Logger();
	void vLog(LogLevel, const char*, va_list);
	
public:
	static Logger& GetInstance();
	void SetLevel(LogLevel);
	void EnableColor(bool flag = true);
	void SetColor(LogLevel, LogColor);
	void SetColor(LogColor debug, LogColor verbose, LogColor info, LogColor warn, LogColor error);
	LogLevel GetLevel() const;

	void Log(LogLevel, std::string, ...);
	void Log(LogLevel, const char*, ...);
	
	void Debug(std::string, ...);
	void Debug(const char*, ...);
	void Debug(bool show_level = false);

	void Verbose(std::string, ...);
	void Verbose(const char*, ...);
	void Verbose(bool show_level = false);
	
	void Info(std::string, ...);
	void Info(const char*, ...);
	void Info(bool show_level = false);
	
	void Warn(std::string, ...);
	void Warn(const char*, ...);
	void Warn(bool show_level = false);
	
	void Error(std::string, ...);
	void Error(const char*, ...);
	void Error(bool show_level = false);

	Logger(const Logger& other) = delete;
	Logger(Logger&& other) noexcept = delete;
	Logger& operator=(const Logger& other) = delete;
	Logger& operator=(Logger&& other) noexcept = delete;
};

