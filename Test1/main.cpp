#include <Game301Engine/Window.h>

#include <iostream>

#include "DemoApp.h"

using namespace ENGINE;

int main(int argc, char* args[]) {
	//Grab an instance of the engine and then tell it that it has a game attached; 
	//Needs to be before the onStart()
	GameEngine::getInstance()->gameInterface = new DemoApp();

	//Create the first instance of the engine
	if (GameEngine::getInstance()->onStart()) {
		//Start the Game Loop
		GameEngine::getInstance()->run();
	}
	return 0;
}