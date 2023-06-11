#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>
#include <InputManager.h>

#include "CreateScenes.h"

void load();

int main(int, char* []) 
{
	dae::Minigin engine{ "../Data/", 640, 540 };
	engine.Run(load);
	return 0;
}

void load()
{
	auto& input = dae::InputManager::GetInstance();
	input.AddXBoxController(0);
	input.AddXBoxController(1);

	CreateMainMenu();
	CreateSinglePlayer();
	CreateCoop();
	CreateVersus();
	CreateInsertName();
	CreateLeaderboard();
}