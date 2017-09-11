#pragma once
#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <fstream>
#include <iomanip>
#include <string>

namespace ENGINE
{

	class LogManager
	{
	public:
		//Log type enumeration
		enum LogType {LOG_NONE, LOG_ERROR, LOG_WARN, LOG_TRACE, LOG_INFO};
		std::string logFileName;

		~LogManager();

		static LogManager* getInstance();

		void openFile(std::string &fileName);
		void closeFile();
		void setLogType(LogType type);
		LogType getLogType();

		//Different log type messages
		void log(LogType type, std::string message);
		void error(std::string message);
		void warn(std::string message);
		void trace(std::string message);
		void info(std::string message);

	private:
		//Private for singleton purposes
		LogManager();

		static LogManager *m_logManagerInstance;
		std::ofstream *m_outStream;
		LogType m_type;
	};

}

#endif