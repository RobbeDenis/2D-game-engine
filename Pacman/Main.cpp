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
#include "SinglePlayer.h"
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
	auto gamemode = go->AddComponent<pacman::SinglePlayer>();

	// Grid test
	go = scene->CreateGameObject();
	auto grid = go->AddComponent<pacman::Grid>();
	auto gridRender = go->AddComponent<pacman::GridRenderer>();
	gridRender->EnableDebugGrid(false);
	gridRender->EnableDebugAgents(false);
	gamemode->AddObserver(gridRender);
	grid->AddObserver(gridRender);
	go->SetLocalPosition(100, 60);
	gamemode->AssignGrid(grid);

	//ScoreDisplay
	go = scene->CreateGameObject();
	auto tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22));
	tr->SetColor({ 255, 255, 255 });
	tr->SetText("SCORE");
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
	auto pacmanObj{ CreatePacman(scene, "pacman.png", grid, { 13,23 }) };
	auto pman{ pacmanObj->GetComponent<pacman::Pacman>() };
	pman->AddObserver(gamemode);
	pman->AddObserver(score);
	pman->AddObserver(lives);
	gamemode->AddPlayer(pman);

	// Ghosts
	gamemode->AddGhost(CreateChaseGhost(scene, "red.png", grid, { 12,14 }, pacmanObj, { 0,0 }));
	gamemode->AddGhost(CreateChaseGhost(scene, "blue.png", grid, { 12,14 }, pacmanObj, { 1,1 }));
	gamemode->AddGhost(CreateChaseGhost(scene, "orange.png", grid, { 14,14 }, pacmanObj, { 1,0 }));
	gamemode->AddGhost(CreateChaseGhost(scene, "pink.png", grid, { 15,14 }, pacmanObj, { 0,1 }));

	// Input
	{
		using namespace dae;

		input.AddKeyboardCommand({ SDL_SCANCODE_W, ButtonState::Pressed }, std::make_shared<MoveCharacter>(0, -1, pman));
		input.AddKeyboardCommand({ SDL_SCANCODE_A, ButtonState::Pressed }, std::make_shared<MoveCharacter>(-1, 0, pman));
		input.AddKeyboardCommand({ SDL_SCANCODE_S, ButtonState::Pressed }, std::make_shared<MoveCharacter>(0, 1, pman));
		input.AddKeyboardCommand({ SDL_SCANCODE_D, ButtonState::Pressed }, std::make_shared<MoveCharacter>(1, 0, pman));

		input.AddKeyboardCommand({ SDL_SCANCODE_F1, ButtonState::Pressed }, std::make_shared<SkipLevel>(gamemode));
	}
}