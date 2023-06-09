#include "CreateScenes.h"

#include <InputManager.h>
#include <ResourceManager.h>

#include "SinglePlayer.h"
#include "CreateObjects.h"
#include "PacmanCommands.h"

dae::Scene* CreateMainMenu()
{
	//auto& input = dae::InputManager::GetInstance();
	auto& sceneManager = dae::SceneManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene("Singleplayer");
	//dae::GameObject* go;

	CreateFPS(scene);

	return scene;
}

dae::Scene* CreateSinglePlayer()
{
	auto& input = dae::InputManager::GetInstance();
	auto& sceneManager = dae::SceneManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene("Singleplayer");
	dae::GameObject* go;

	CreateFPS(scene);

	go = scene->CreateGameObject();
	auto gamemode = go->AddComponent<pacman::SinglePlayer>();
	auto grid = CreateGrid(scene, gamemode, 100, 60);
	auto score = CreateScoreDisplay(scene, { 255,255,255 }, 75, 10);
	auto lives = CreateLivesDisplay(scene, "pacman.png", gamemode, 20, 400);

	auto pacmanObj{ CreatePacman(scene, "pacman.png", grid, { 13,23 }) };
	auto player{ pacmanObj->GetComponent<pacman::Pacman>() };
	player->AddObserver(gamemode);
	player->AddObserver(score);
	player->AddObserver(lives);
	gamemode->AddPlayer(player);

	gamemode->AddGhost(CreateGhost(scene, "red.png", grid, { 12,14 }, pacmanObj, { 0,0 }));
	gamemode->AddGhost(CreateGhost(scene, "blue.png", grid, { 12,14 }, pacmanObj, { 1,1 }));
	gamemode->AddGhost(CreateGhost(scene, "orange.png", grid, { 14,14 }, pacmanObj, { 1,0 }));
	gamemode->AddGhost(CreateGhost(scene, "pink.png", grid, { 15,14 }, pacmanObj, { 0,1 }));

	{
		using namespace dae;

		input.AddKeyboardCommand({ SDL_SCANCODE_W, ButtonState::Pressed }, std::make_shared<MoveCharacter>(0, -1, player));
		input.AddKeyboardCommand({ SDL_SCANCODE_A, ButtonState::Pressed }, std::make_shared<MoveCharacter>(-1, 0, player));
		input.AddKeyboardCommand({ SDL_SCANCODE_S, ButtonState::Pressed }, std::make_shared<MoveCharacter>(0, 1, player));
		input.AddKeyboardCommand({ SDL_SCANCODE_D, ButtonState::Pressed }, std::make_shared<MoveCharacter>(1, 0, player));

		input.AddKeyboardCommand({ SDL_SCANCODE_F1, ButtonState::Pressed }, std::make_shared<SkipLevel>(gamemode));
	}

	return scene;
}