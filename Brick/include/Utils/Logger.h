#pragma once
#include "config.h"

#if defined(_WIN32) && LOG_COLOR
#include <Windows.h>
#endif

#include <string>
#include <mutex>

#include <stdio.h>
#include <stdarg.h>

enum class LogLevel:int
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
	static Logger* _instance;

	Logger();
	void vLog(LogLevel, const char*, va_list);
	
public:
	static Logger* GetInstance();

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
};

