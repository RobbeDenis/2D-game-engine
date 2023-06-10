#include "CreateScenes.h"

#include <InputManager.h>
#include <ResourceManager.h>
#include <XBox360Controller.h>

#include "SinglePlayer.h"
#include "CreateObjects.h"
#include "PacmanCommands.h"
#include "Selector.h"
#include "SceneIds.h"

dae::Scene* CreateMainMenu()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene(SceneId::Mainmanu);
	dae::GameObject* go = scene->CreateGameObject();


	auto sr = go->AddComponent<dae::SpriteRenderer>();
	sr->SetTexture("MainMenu.png");

	go = scene->CreateGameObject();
	sr = go->AddComponent<dae::SpriteRenderer>();
	sr->SetTexture("Selector.png");
	auto selector = go->AddComponent<pacman::Selector>();

	const int startY{ 176 };
	const int stepY{ 64 };
	selector->AddIndex({ 195, startY }, SceneId::Singleplayer);
	selector->AddIndex({ 240, startY + stepY }, SceneId::Coop);
	selector->AddIndex({ 237, startY + stepY * 2}, SceneId::Versus);
	selector->AddIndex({ 221, startY + stepY * 3}, SceneId::Controls);
	selector->AddIndex({ 190, startY + stepY * 4}, SceneId::Leaderboard);
	selector->SetIndex(0);

	CreateFPS(scene);

	{
		using namespace dae;
		using namespace commands;
		using namespace xbox;

		std::shared_ptr<KeyboardCommandsMap> kMap{ std::make_shared<KeyboardCommandsMap>() };
		std::shared_ptr<ControllerCommandsMap> cMap{ std::make_shared<ControllerCommandsMap>() };

		auto up{ std::make_shared<MoveSelector>(selector, -1) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_W, ButtonState::Pressed }, up);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_UP, ButtonState::Pressed }, up);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonUp, ButtonState::Pressed }, up);

		auto down{ std::make_shared<MoveSelector>(selector, 1) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_S, ButtonState::Pressed }, down);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_DOWN, ButtonState::Pressed }, down);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonDown, ButtonState::Pressed }, down);

		auto confirm{ std::make_shared<ConfirmSelector>(selector) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_SPACE, ButtonState::Pressed }, confirm);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN, ButtonState::Pressed }, confirm);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN2, ButtonState::Pressed }, confirm);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_KP_ENTER, ButtonState::Pressed }, confirm);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonA, ButtonState::Pressed }, confirm);

		auto quitApp{ std::make_shared<QuitApplication>() };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_ESCAPE, ButtonState::Released }, quitApp);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released }, quitApp);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released }, quitApp);

		scene->SetKeyboardCommands(kMap);
		scene->SetControllerCommands(cMap);
	}

	return scene;
}

dae::Scene* CreateLeaderboard()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene(SceneId::Leaderboard);
	//dae::GameObject* go = scene->CreateGameObject();

	{
		using namespace dae;
		using namespace commands;
		using namespace xbox;

		std::shared_ptr<KeyboardCommandsMap> kMap{ std::make_shared<KeyboardCommandsMap>() };
		std::shared_ptr<ControllerCommandsMap> cMap{ std::make_shared<ControllerCommandsMap>() };

		auto SetMainScene{ std::make_shared<SetScene>(SceneId::Mainmanu) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_SPACE, ButtonState::Pressed }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN, ButtonState::Pressed }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN2, ButtonState::Pressed }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_KP_ENTER, ButtonState::Pressed }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonA, ButtonState::Pressed }, SetMainScene);

		scene->SetKeyboardCommands(kMap);
		scene->SetControllerCommands(cMap);
	}

	return scene;
}

dae::Scene* CreateSinglePlayer()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene(SceneId::Singleplayer);
	dae::GameObject* go;

	CreateFPS(scene);

	go = scene->CreateGameObject();
	auto gamemode = go->AddComponent<pacman::SinglePlayer>();
	auto grid = CreateGrid(scene, gamemode, 100, 60);
	auto score = CreateScoreDisplay(scene, { 255,255,255 }, 75, 10);
	CreateHighscore(scene, { 255,255,255 }, 220, 10);
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
		using namespace commands;
		using namespace xbox;

		std::shared_ptr<KeyboardCommandsMap> kMap{ std::make_shared<KeyboardCommandsMap>() };
		std::shared_ptr<ControllerCommandsMap> cMap{ std::make_shared<ControllerCommandsMap>() };

		auto up{ std::make_shared<MoveCharacter>(0, -1, player) };
		auto down{ std::make_shared<MoveCharacter>(0, 1, player) };
		auto left{ std::make_shared<MoveCharacter>(-1, 0, player) };
		auto right{ std::make_shared<MoveCharacter>(1, 0, player) };

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_W, ButtonState::Pressed }, up);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_S, ButtonState::Pressed }, down);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_A, ButtonState::Pressed }, left);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_D, ButtonState::Pressed }, right);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_UP, ButtonState::Pressed }, up);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_DOWN, ButtonState::Pressed }, down);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_LEFT, ButtonState::Pressed }, left);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RIGHT, ButtonState::Pressed }, right);

		input.AddControllerCommand(cMap, { XBoxButton::ButtonUp, ButtonState::Pressed }, up);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonDown, ButtonState::Pressed }, down);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonLeft, ButtonState::Pressed }, left);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonRight, ButtonState::Pressed }, right);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_F1, ButtonState::Pressed }, std::make_shared<SkipLevel>(gamemode));

		auto SetMainScene{ std::make_shared<SetScene>(SceneId::Mainmanu) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_ESCAPE, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released }, SetMainScene);

		scene->SetKeyboardCommands(kMap);
		scene->SetControllerCommands(cMap);
	}

	return scene;
}