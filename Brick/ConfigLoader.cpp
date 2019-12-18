#include "ConfigLoader.h"

std::map<std::string, std::string> ConfigLoader::_config;

void ConfigLoader::Parse(std::string filepath)
{
	Logger& logger = Logger::GetInstance();

	logger.Debug("Opening Config File : %s", filepath.c_str());
	std::ifstream f(filepath);
	if (!f.good())
	{
		logger.Error("Failed to Open Config File on config.txt");
		return;
	}
	
	std::string line;
	while (std::getline(f, line))
	{
		logger.Debug("Parser Read : %s", line.c_str());
		line = trim(line);

		if (line.empty())
		{
			logger.Debug("\tEmpty Line Detected, Skipping");
			continue;
		}
		
		if (line[0] == '#')
		{
			logger.Debug("\tParser Found '#'");
			logger.Debug("\tAssuming This Line is a Comment");
			continue;
		}

		const int index = line.find('=');
		std::string key = line.substr(0, index);
		key = trim(key);
		
		std::string value = line.substr(1 + index);
		value = trim(value);

		_config.insert(std::make_pair(key, value));
	}
	
	f.close();
}

int ConfigLoader::Load(int argc, char* argv[])
{
	_config = std::map<std::string, std::string>();
	Logger& logger = Logger::GetInstance();

	std::string configPath = "config.txt";
	for (int i = 1; i < argc; ++i)
	{
		logger.Debug("Argument #%02d : %s", i, argv[i]);
		switch(strhash(argv[i]))
		{
		case strhash("-d"):
			logger.SetLevel(LogLevel::DEBG);
			logger.Debug("\tFound Debug Flag in arguments");
			if (i != 1)
			{
				logger.Warn("\tDebug Flag was not the first flag");
				logger.Warn("\tSome messages could have been omitted");
			}
			break;
		case strhash("-v"):
			logger.Debug("\tFound Verbose Flag in arguments");
			if (logger.GetLevel() < LogLevel::VERB)
			{
				logger.Warn("\tLog Level Previously set to Debug");
				logger.Warn("\tLog Level Will be Fixed to Debug");
			}
			else
			{
				logger.SetLevel(LogLevel::VERB);
			}
		case strhash("-c"):
			logger.Debug("\tFound Color Flag in arguments");
			logger.EnableColor();
			break;
		case strhash("-f"):
			logger.Debug("\tFound Config File Path in arguments");
			logger.Debug("\tConfig File Path : %s", argv[i]);

			i++; //Next Argument
			if (i >= argc)
			{
				return 2;
			}
			configPath = argv[i];
		default:
			return 1;
		}
	}

	Parse(configPath);
	return 0;
}


bool ConfigLoader::GetBool(std::string key)
{
	if (!_config.count(key))
	{
		return false;
	}
	std::string value = _config[key];
	
	std::transform(value.begin(), value.end(), value.begin(), std::toupper);
	return value == "TRUE";
}

int ConfigLoader::GetInt(std::string key)
{
	if (!_config.count(key))
	{
		return -1;
	}
	return std::stoi(_config[key]);
}

std::string ConfigLoader::GetString(std::string key)
{
	if (!_config.count(key))
	{
		return nullptr;
	}
	return _config[key];
}
