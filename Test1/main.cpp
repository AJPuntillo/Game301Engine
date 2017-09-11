#include <Game301Engine/LogManager.h>

#include <iostream>

int main()
{
	ENGINE::LogManager::getInstance()->setLogType(ENGINE::LogManager::LOG_INFO);
	ENGINE::LogManager::getInstance()->error("1");
	ENGINE::LogManager::getInstance()->warn("2");
	ENGINE::LogManager::getInstance()->trace("3");
	ENGINE::LogManager::getInstance()->info("4");

	return 0;
}