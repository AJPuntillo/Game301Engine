#include "LogManager.h"

using namespace ENGINE;

//Set the instance to NULL so that it initializes
LogManager *LogManager::m_logManagerInstance = nullptr;

LogManager::LogManager()
{
	//Empty
};

LogManager::~LogManager()
{
	closeFile();
};

LogManager* LogManager::getInstance()
{
	if (m_logManagerInstance == nullptr) {
		m_logManagerInstance = new LogManager();
	}
	return m_logManagerInstance;
}

void LogManager::openFile(std::string &fileName)
{
	closeFile();
	m_outStream = new std::ofstream(fileName.c_str());
}

void LogManager::closeFile()
{
	if (m_outStream != nullptr) {
		m_outStream->close();
		delete m_outStream;
		m_outStream = nullptr;
	}
}

void LogManager::setLogType(LogType type)
{
	m_type = type;
}

LogManager::LogType LogManager::getLogType()
{
	return m_type;
}

//***Different levels of log types***

void LogManager::log(LogType type, std::string message)
{
	if (type <= m_type && m_type > LOG_NONE)
	{
		if (m_outStream == nullptr)
		{
			openFile(logFileName);
		}
		(*m_outStream) << message << "\n";
		m_outStream->flush();
	}
}

void LogManager::error(std::string message)
{
	message.insert(0, "ERROR: ");
	log(LOG_ERROR, message);
}

void LogManager::warn(std::string message)
{
	message.insert(0, "WARN: ");
	log(LOG_WARN, message);
}

void LogManager::trace(std::string message)
{
	message.insert(0, "TRACE: ");
	log(LOG_TRACE, message);
}

void LogManager::info(std::string message)
{
	message.insert(0, "INFO: ");
	log(LOG_INFO, message);
}
