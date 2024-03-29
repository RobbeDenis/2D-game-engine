#include "CreateScenes.h"

#include <InputManager.h>
#include <ResourceManager.h>
#include <XBox360Controller.h>

#include "SinglePlayer.h"
#include "CreateObjects.h"
#include "PacmanCommands.h"
#include "Selector.h"
#include "SceneIds.h"
#include "Leaderboard.h"
#include "TypeName.h"
#include "Coop.h"

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
		input.AddControllerCommand(cMap, { XBoxButton::ButtonUp, ButtonState::Pressed, 1 }, up);

		auto down{ std::make_shared<MoveSelector>(selector, 1) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_S, ButtonState::Pressed }, down);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_DOWN, ButtonState::Pressed }, down);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonDown, ButtonState::Pressed }, down);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonDown, ButtonState::Pressed, 1 }, down);

		auto confirm{ std::make_shared<ConfirmSelector>(selector) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_SPACE, ButtonState::Released }, confirm);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN, ButtonState::Released }, confirm);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN2, ButtonState::Released }, confirm);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_KP_ENTER, ButtonState::Released }, confirm);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonA, ButtonState::Released }, confirm);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonA, ButtonState::Released, 1 }, confirm);

		auto quitApp{ std::make_shared<QuitApplication>() };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_ESCAPE, ButtonState::Released }, quitApp);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released }, quitApp);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released, 1 }, quitApp);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released }, quitApp);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released, 1 }, quitApp);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_M, ButtonState::Released }, std::make_shared<ToggleMute>());

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
	dae::GameObject* go = scene->CreateGameObject();

	go->AddComponent<pacman::Leaderboard>();
	go->SetLocalPosition(200, 150);

	{
		using namespace dae;
		using namespace commands;
		using namespace xbox;

		std::shared_ptr<KeyboardCommandsMap> kMap{ std::make_shared<KeyboardCommandsMap>() };
		std::shared_ptr<ControllerCommandsMap> cMap{ std::make_shared<ControllerCommandsMap>() };

		auto SetMainScene{ std::make_shared<SetScene>(SceneId::Mainmanu) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_SPACE, ButtonState::Released }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_ESCAPE, ButtonState::Released }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN, ButtonState::Released }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN2, ButtonState::Released }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_KP_ENTER, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonA, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonA, ButtonState::Released, 1 }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released, 1 }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released, 1 }, SetMainScene);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_M, ButtonState::Released }, std::make_shared<ToggleMute>());

		scene->SetKeyboardCommands(kMap);
		scene->SetControllerCommands(cMap);
	}

	return scene;
}

dae::Scene* CreateInsertName()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene(SceneId::InsertName);
	dae::GameObject* go = scene->CreateGameObject();

	auto name = go->AddComponent<pacman::TypeName>();
	go->AddComponent<dae::TextRenderer>();
	go->SetLocalPosition(280, 245);

	go = scene->CreateGameObject();
	go->AddComponent<dae::TextRenderer>()->SetText("FILL IN YOUR NAME");
	go->SetLocalPosition(160, 200);

	{
		using namespace dae;
		using namespace commands;
		using namespace xbox;

		std::shared_ptr<KeyboardCommandsMap> kMap{ std::make_shared<KeyboardCommandsMap>() };
		std::shared_ptr<ControllerCommandsMap> cMap{ std::make_shared<ControllerCommandsMap>() };

		auto confirm{ std::make_shared<ConfirmName>(name) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_SPACE, ButtonState::Released }, confirm);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN, ButtonState::Released }, confirm);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN2, ButtonState::Released }, confirm);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_KP_ENTER, ButtonState::Released }, confirm);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonA, ButtonState::Released }, confirm);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonA, ButtonState::Released, 1 }, confirm);

		auto up{ std::make_shared<ChangeNameCharacter>(name, static_cast<char>(1)) };
		auto down{ std::make_shared<ChangeNameCharacter>(name, static_cast<char>(-1)) };
		auto left{ std::make_shared<ChangeNameIndex>(name, static_cast<char>(-1)) };
		auto right{ std::make_shared<ChangeNameIndex>(name, static_cast<char>(1)) };

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_W, ButtonState::Pressed }, up);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_S, ButtonState::Pressed }, down);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_A, ButtonState::Pressed }, left);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_D, ButtonState::Pressed }, right);

		input.AddControllerCommand(cMap, { XBoxButton::ButtonUp, ButtonState::Pressed }, up);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonUp, ButtonState::Pressed, 1 }, up);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonDown, ButtonState::Pressed }, down);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonDown, ButtonState::Pressed, 1 }, down);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonLeft, ButtonState::Pressed }, left);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonLeft, ButtonState::Pressed, 1 }, left);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonRight, ButtonState::Pressed }, right);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonRight, ButtonState::Pressed, 1 }, right);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_M, ButtonState::Released }, std::make_shared<ToggleMute>());

		scene->SetKeyboardCommands(kMap);
		scene->SetControllerCommands(cMap);
	}

	return scene;
}

dae::Scene* CreateControls()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene(SceneId::Controls);
	dae::GameObject* go = scene->CreateGameObject();

	go->AddComponent<dae::TextRenderer>()->SetText("                            KBM            Controller");
	go->SetLocalPosition(0, 7);

	int y{ 60 };
	int offset{ 44 };

	go = go = scene->CreateGameObject();
	go->SetLocalPosition(0, y);
	go->AddComponent<dae::TextRenderer>()->SetText("Confirm:   SPACE/ENTER           A");

	go = go = scene->CreateGameObject();
	go->SetLocalPosition(0, y + offset);
	go->AddChild()->AddComponent<dae::TextRenderer>()->SetText("Move:         WASD/Arrows       Arrows");

	go = go = scene->CreateGameObject();
	go->SetLocalPosition(0, y + offset * 2);
	go->AddChild()->AddComponent<dae::TextRenderer>()->SetText("Mute:                    M");

	go = go = scene->CreateGameObject();
	go->SetLocalPosition(0, y + offset * 3);
	go->AddChild()->AddComponent<dae::TextRenderer>()->SetText("Skip level:            F1");

	go = go = scene->CreateGameObject();
	go->SetLocalPosition(0, y + offset * 4);
	go->AddChild()->AddComponent<dae::TextRenderer>()->SetText("Kill player:          1/2");

	go = go = scene->CreateGameObject();
	go->SetLocalPosition(0, y + offset * 5);
	go->AddChild()->AddComponent<dae::TextRenderer>()->SetText("Quit/Back:        ESCP                 BACK");


	{
		using namespace dae;
		using namespace commands;
		using namespace xbox;

		std::shared_ptr<KeyboardCommandsMap> kMap{ std::make_shared<KeyboardCommandsMap>() };
		std::shared_ptr<ControllerCommandsMap> cMap{ std::make_shared<ControllerCommandsMap>() };

		auto SetMainScene{ std::make_shared<SetScene>(SceneId::Mainmanu) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_SPACE, ButtonState::Released }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_ESCAPE, ButtonState::Released }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN, ButtonState::Released }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RETURN2, ButtonState::Released }, SetMainScene);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_KP_ENTER, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonA, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonA, ButtonState::Released, 1 }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released, 1 }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released, 1 }, SetMainScene);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_M, ButtonState::Released }, std::make_shared<ToggleMute>());

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

	auto pacmanObj{ CreatePacman(scene, "ss_pacman.png", grid, { 13,23 }) };
	auto player{ pacmanObj->GetComponent<pacman::Pacman>() };
	player->AddObserver(gamemode);
	player->AddObserver(score);
	player->AddObserver(lives);
	gamemode->AddPlayer(player);

	gamemode->AddGhost(CreateGhost(scene, "ss_red.png", grid, { 12,14 }, pacmanObj, { 0,0 }));
	gamemode->AddGhost(CreateGhost(scene, "ss_blue.png", grid, { 12,14 }, pacmanObj, { 1,1 }));
	gamemode->AddGhost(CreateGhost(scene, "ss_orange.png", grid, { 14,14 }, pacmanObj, { 1,0 }));
	gamemode->AddGhost(CreateGhost(scene, "ss_pink.png", grid, { 15,14 }, pacmanObj, { 0,1 }));

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


		auto SetMainScene{ std::make_shared<SetScene>(SceneId::Mainmanu) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_ESCAPE, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released }, SetMainScene);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_F1, ButtonState::Pressed }, std::make_shared<SkipLevel>(gamemode));
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_KP_1, ButtonState::Pressed }, std::make_shared<KillPacman>(player));

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_M, ButtonState::Released }, std::make_shared<ToggleMute>());

		scene->SetKeyboardCommands(kMap);
		scene->SetControllerCommands(cMap);
	}

	return scene;
}

dae::Scene* CreateCoop()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene(SceneId::Coop);
	dae::GameObject* go;

	CreateFPS(scene);

	go = scene->CreateGameObject();
	auto gamemode = go->AddComponent<pacman::Coop>();
	auto grid = CreateGrid(scene, gamemode, 100, 60);
	auto score = CreateScoreDisplay(scene, { 255,255,255 }, 75, 10);
	CreateHighscore(scene, { 255,255,255 }, 220, 10);
	auto lives1 = CreateLivesDisplay(scene, "pacman.png", gamemode, 20, 400);
	auto lives2 = CreateLivesDisplay(scene, "mspacman.png", gamemode, 555, 400);

	auto pacmanObj1{ CreatePacman(scene, "ss_pacman.png", grid, { 6,22 }) };
	auto player1{ pacmanObj1->GetComponent<pacman::Pacman>() };
	player1->AddObserver(gamemode);
	player1->AddObserver(score);
	player1->AddObserver(lives1);
	gamemode->AddPlayer1(player1);

	auto pacmanObj2{ CreatePacman(scene, "ss_mspacman.png", grid, { 20,22 }) };
	auto player2{ pacmanObj2->GetComponent<pacman::Pacman>() };
	player2->SetPlaySound(false);
	player2->AddObserver(gamemode);
	player2->AddObserver(score);
	player2->AddObserver(lives2);
	gamemode->AddPlayer2(player2);

	gamemode->AddGhost(CreateGhost(scene, "ss_red.png", grid, { 12,14 }, pacmanObj1, { 0,0 }));
	gamemode->AddGhost(CreateGhost(scene, "ss_blue.png", grid, { 12,14 }, pacmanObj1, { 1,1 }));
	gamemode->AddGhost(CreateGhost(scene, "ss_orange.png", grid, { 14,14 }, pacmanObj2, { 1,0 }));
	gamemode->AddGhost(CreateGhost(scene, "ss_pink.png", grid, { 15,14 }, pacmanObj2, { 0,1 }));

	{
		using namespace dae;
		using namespace commands;
		using namespace xbox;

		std::shared_ptr<KeyboardCommandsMap> kMap{ std::make_shared<KeyboardCommandsMap>() };
		std::shared_ptr<ControllerCommandsMap> cMap{ std::make_shared<ControllerCommandsMap>() };

		auto up{ std::make_shared<MoveCharacter>(0, -1, player1) };
		auto down{ std::make_shared<MoveCharacter>(0, 1, player1) };
		auto left{ std::make_shared<MoveCharacter>(-1, 0, player1) };
		auto right{ std::make_shared<MoveCharacter>(1, 0, player1) };

		input.AddControllerCommand(cMap, { XBoxButton::ButtonUp, ButtonState::Pressed }, up);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonDown, ButtonState::Pressed }, down);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonLeft, ButtonState::Pressed }, left);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonRight, ButtonState::Pressed }, right);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_W, ButtonState::Pressed }, up);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_S, ButtonState::Pressed }, down);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_A, ButtonState::Pressed }, left);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_D, ButtonState::Pressed }, right);

		auto up2{ std::make_shared<MoveCharacter>(0, -1, player2) };
		auto down2{ std::make_shared<MoveCharacter>(0, 1, player2) };
		auto left2{ std::make_shared<MoveCharacter>(-1, 0, player2) };
		auto right2{ std::make_shared<MoveCharacter>(1, 0, player2) };

		input.AddControllerCommand(cMap, { XBoxButton::ButtonUp, ButtonState::Pressed, 1 }, up2);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonDown, ButtonState::Pressed, 1 }, down2);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonLeft, ButtonState::Pressed, 1 }, left2);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonRight, ButtonState::Pressed, 1 }, right2);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_UP, ButtonState::Pressed }, up2);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_DOWN, ButtonState::Pressed }, down2);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_LEFT, ButtonState::Pressed }, left2);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RIGHT, ButtonState::Pressed }, right2);


		auto SetMainScene{ std::make_shared<SetScene>(SceneId::Mainmanu) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_ESCAPE, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released, 1 }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released, 1 }, SetMainScene);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_F1, ButtonState::Pressed }, std::make_shared<SkipLevel>(gamemode));
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_KP_1, ButtonState::Pressed }, std::make_shared<KillPacman>(player1));
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_KP_2, ButtonState::Pressed }, std::make_shared<KillPacman>(player2));

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_M, ButtonState::Released }, std::make_shared<ToggleMute>());

		scene->SetKeyboardCommands(kMap);
		scene->SetControllerCommands(cMap);
	}

	return scene;
}

dae::Scene* CreateVersus()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene(SceneId::Versus);
	dae::GameObject* go;

	CreateFPS(scene);

	go = scene->CreateGameObject();
	auto gamemode = go->AddComponent<pacman::SinglePlayer>();
	auto grid = CreateGrid(scene, gamemode, 100, 60);
	auto score = CreateScoreDisplay(scene, { 255,255,255 }, 75, 10);
	CreateHighscore(scene, { 255,255,255 }, 220, 10);
	auto lives = CreateLivesDisplay(scene, "pacman.png", gamemode, 20, 400);

	auto pacmanObj{ CreatePacman(scene, "ss_pacman.png", grid, { 13,23 }) };
	auto player{ pacmanObj->GetComponent<pacman::Pacman>() };
	player->AddObserver(gamemode);
	player->AddObserver(score);
	player->AddObserver(lives);
	gamemode->AddPlayer(player);

	auto playerGhost{ CreateGhost(scene, "ss_red.png", grid, { 12,14 }, pacmanObj, { 0,0 }) };
	playerGhost->SetControlled();

	gamemode->AddGhost(playerGhost);
	gamemode->AddGhost(CreateGhost(scene, "ss_blue.png", grid, { 12,14 }, pacmanObj, { 1,1 }));
	gamemode->AddGhost(CreateGhost(scene, "ss_orange.png", grid, { 14,14 }, pacmanObj, { 1,0 }));
	gamemode->AddGhost(CreateGhost(scene, "ss_pink.png", grid, { 15,14 }, pacmanObj, { 0,1 }));

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

		input.AddControllerCommand(cMap, { XBoxButton::ButtonUp, ButtonState::Pressed }, up);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonDown, ButtonState::Pressed }, down);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonLeft, ButtonState::Pressed }, left);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonRight, ButtonState::Pressed }, right);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_W, ButtonState::Pressed }, up);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_S, ButtonState::Pressed }, down);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_A, ButtonState::Pressed }, left);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_D, ButtonState::Pressed }, right);

		auto up2{ std::make_shared<MoveCharacter>(0, -1, playerGhost) };
		auto down2{ std::make_shared<MoveCharacter>(0, 1, playerGhost) };
		auto left2{ std::make_shared<MoveCharacter>(-1, 0, playerGhost) };
		auto right2{ std::make_shared<MoveCharacter>(1, 0, playerGhost) };

		input.AddControllerCommand(cMap, { XBoxButton::ButtonUp, ButtonState::Pressed, 1 }, up2);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonDown, ButtonState::Pressed, 1 }, down2);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonLeft, ButtonState::Pressed, 1 }, left2);
		input.AddControllerCommand(cMap, { XBoxButton::ButtonRight, ButtonState::Pressed, 1 }, right2);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_UP, ButtonState::Pressed }, up2);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_DOWN, ButtonState::Pressed }, down2);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_LEFT, ButtonState::Pressed }, left2);
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_RIGHT, ButtonState::Pressed }, right2);


		auto SetMainScene{ std::make_shared<SetScene>(SceneId::Mainmanu) };
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_ESCAPE, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Back, ButtonState::Released, 1 }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released }, SetMainScene);
		input.AddControllerCommand(cMap, { XBoxButton::Start, ButtonState::Released, 1 }, SetMainScene);

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_F1, ButtonState::Pressed }, std::make_shared<SkipLevel>(gamemode));
		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_KP_1, ButtonState::Pressed }, std::make_shared<KillPacman>(player));

		input.AddKeyboardCommand(kMap, { SDL_SCANCODE_M, ButtonState::Released }, std::make_shared<ToggleMute>());

		scene->SetKeyboardCommands(kMap);
		scene->SetControllerCommands(cMap);
	}

	return scene;
}
