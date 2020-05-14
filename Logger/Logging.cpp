#include "Logging.h"


Logging::Logging(std::ostream& out, Level minLogLevel) : m_out(out), m_level(minLogLevel)
{
}

void Logging::Log(const std::string& message, Level logLevel)
{
	if (logLevel >= m_level)
		m_out << message << std::endl;
}
