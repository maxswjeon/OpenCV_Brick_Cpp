#pragma once
#include "Utilities.h"
#include "Logger.h"

#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <functional>

struct LoggerConfig
{
    bool Color;
    LogLevel Level;
	
};

class ConfigLoader
{
    static std::map<std::string, std::string> _config;
	
    static inline std::string trim(std::string s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
        s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }

	static void Parse(std::string);
public:	
	static int Load(int argc, char* argv[]);
    static bool GetBool(std::string key);
    static int GetInt(std::string key);
    static std::string GetString(std::string key);
};

