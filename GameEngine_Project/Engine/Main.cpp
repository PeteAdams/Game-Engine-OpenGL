#ifndef MAIN
#define MAIN

#include "../Engine/Core/CoreEngine.h"
#include "../Game/Game1.h"

int main(int argc, char* argv[]) 
{
	CoreEngine::GetInstance()->SetGameInterface(new Game1());

	if (CoreEngine::GetInstance()->OnCreate("Game302 Game and Engine", 800, 600))
	{
		std::cout << "Window Successfully Loaded! :D" << std::endl;
	}

	else if (!CoreEngine::GetInstance()->OnCreate("GAME302 Game and Engine", 800, 600)) {
		std::cout << "Unable to load window." << std::endl;
		return 0;
	}
	CoreEngine::GetInstance()->Run();

	return 0;
}

#endif