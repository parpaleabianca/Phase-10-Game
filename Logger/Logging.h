#pragma once

#include<ostream>

#ifdef LOGGING_EXPORTS
#define API_LOGGER __declspec(dllexport)
#else
#define API_LOGGER __declspec(dllimport)
#endif


class API_LOGGER Logging
{
public:
	enum class Level
	{
		Debug,
		Info,
		Warning,
		Error
	};

public:
	Logging(std::ostream& out, Level minLogLevel);
	void Log(const std::string& message, Level logLevel);

private:
	std::ostream& m_out;
	Level m_level;
};

