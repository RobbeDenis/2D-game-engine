#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>

#include "ResourceManager.h"
#include "Scene.h"
#include "Component.h"
#include "TestComp.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "FPSCounter.h"
#include "RotateParent.h"
#include "ImGuiRenderer.h"
#include "TrashTheCash.h"
#include "InputManager.h"
#include "XBox360Controller.h"
#include "TestCommands.h"
#include "TestCharacter.h"
#include "GameEvents.h"
#include "ScoreDisplay.h"
#include "GridRenderer.h"
#include "Character.h"
#include "PacmanCommands.h"
#include "SoundSystemLocator.h"
#include "LoggerSoundSystem.h"
#include "SDLSoundSystem.h"
#include "PacmanSounds.h"
#include "LivesRender.h"
#include "LivesDisplay.h"

#include "GameplayManager.h"
#include "CreateObjects.h"

void load();

int main(int, char* []) 
{
	dae::Minigin engine{ "../Data/", 640, 540 };
	engine.Run(load);
	return 0;
}

void load()
{
	auto& input = dae::InputManager::GetInstance(); input;
	auto& sceneManager = dae::SceneManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene("Demo");
	dae::GameObject* go;

	// FPS
	go = scene->CreateGameObject();
	auto font2 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto tr2 = go->AddComponent<dae::TextRenderer>();
	tr2->SetText("FPS");
	tr2->SetFont(font2);
	tr2->SetColor({ 0, 255, 0 });
	go->AddComponent<dae::FPSCounter>();

	// Gameplay manager
	go = scene->CreateGameObject();
	auto gameplay = go->AddComponent<pacman::GameplayManager>();

	// Grid test
	go = scene->CreateGameObject();
	auto grid = go->AddComponent<pacman::Grid>();
	grid->LoadFromFile(27, 29, 16, "TestLevel.txt");
	grid->PrintGrid();
	auto gridRender = go->AddComponent<pacman::GridRenderer>();
	gridRender->EnableDebugGrid(false);
	gridRender->EnableDebugAgents(false);
	grid->AddObserver(gridRender);
	go->SetLocalPosition(60, 60);

	//ScoreDisplay
	go = scene->CreateGameObject();
	auto tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22));
	tr->SetColor({ 255, 255, 255 });
	tr->SetText("1UP");
	go->SetLocalPosition(75,10);
	go = go->AddChild();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 19));
	tr->SetColor({ 255, 255, 255 });
	auto score = go->AddComponent<pacman::ScoreDisplay>();
	go->SetLocalPosition(20, 19);

	//LivesDisplay
	go = scene->CreateGameObject();
	auto lives = go->AddComponent<pacman::LivesDisplay>();
	auto lr = go->AddComponent<pacman::LivesRender>();
	lr->SetLivesDisplay(lives);
	lr->SetTexture("pacman.png");
	go->SetLocalPosition(20, 400);

	// Player
	auto pacmanObj{ CreatePacman(scene, "pacman.png", grid, { 5,1 }) };
	auto pacman{ pacmanObj->GetComponent<pacman::Pacman>() };
	pacman->AddObserver(gameplay);
	pacman->AddObserver(score);
	pacman->AddObserver(lives);

	// Ghosts
	gameplay->AddGhost(CreateRandomGhost(scene, "red.png", grid, { 11,14 }));
	gameplay->AddGhost(CreateChaseGhost(scene, "blue.png", grid, { 12,14 }, pacmanObj, { 1,1 }));
	gameplay->AddGhost(CreateChaseGhost(scene, "orange.png", grid, { 14,14 }, pacmanObj, { 1,0 }));
	gameplay->AddGhost(CreateChaseGhost(scene, "pink.png", grid, { 15,14 }, pacmanObj, { 0,1 }));

	// Input
	{
		using namespace dae;

		input.AddKeyboardCommand({ SDL_SCANCODE_W, ButtonState::Pressed }, std::make_shared<MoveCharacter>(0, -1, pacman));
		input.AddKeyboardCommand({ SDL_SCANCODE_A, ButtonState::Pressed }, std::make_shared<MoveCharacter>(-1, 0, pacman));
		input.AddKeyboardCommand({ SDL_SCANCODE_S, ButtonState::Pressed }, std::make_shared<MoveCharacter>(0, 1, pacman));
		input.AddKeyboardCommand({ SDL_SCANCODE_D, ButtonState::Pressed }, std::make_shared<MoveCharacter>(1, 0, pacman));
	}
}