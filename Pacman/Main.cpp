#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>

#include "SceneManager.h"
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
#include "LivesDisplay.h"
#include "GameEvents.h"
#include "ScoreDisplay.h"

void load();

int main(int, char* []) 
{
	dae::Minigin engine{ "../Data/" };
	engine.Run(load);
	return 0;
}

void load()
{
	auto& input = dae::InputManager::GetInstance(); input;
	auto& sceneManager = dae::SceneManager::GetInstance();

	dae::Scene* scene = sceneManager.CreateScene("Demo");
	dae::GameObject* go;

	// BACKGROUND
	go = scene->CreateGameObject();
	go->AddComponent<dae::SpriteRenderer>()->SetTexture("background.tga");

	go = scene->CreateGameObject();
	go->AddComponent<dae::SpriteRenderer>()->SetTexture("logo.tga");
	go->SetLocalPosition(216, 180);

	go = scene->CreateGameObject();
	auto tr = go->AddComponent<dae::TextRenderer>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	tr->SetText("Programming 4 Assignment");
	tr->SetFont(font);
	go->SetLocalPosition(90, 0);

	// FPS
	go = scene->CreateGameObject();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetText("FPS");
	tr->SetFont(font);
	tr->SetColor({ 0, 255, 0 });
	go->AddComponent<dae::FPSCounter>();

	// DISPLAY
	SDL_Color yellow{ 252, 219, 3 };
	SDL_Color green{ 0, 217, 22 };

	// Lives display
	go = scene->CreateGameObject();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	tr->SetColor(yellow);
	tr->SetText("Press 1");
	go->SetLocalPosition({ 200, 320, 0 });

	go = scene->CreateGameObject();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	tr->SetColor(yellow);
	auto livesDisplayP1 = go->AddComponent<dae::LivesDisplay>();
	go->SetLocalPosition({ 30, 320, 0 });

	go = scene->CreateGameObject();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	tr->SetColor(green);
	tr->SetText("Press 2");
	go->SetLocalPosition({ 200, 400, 0 });

	go = scene->CreateGameObject();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	tr->SetColor(green);
	auto livesDisplayP2 = go->AddComponent<dae::LivesDisplay>();
	go->SetLocalPosition({ 30, 400, 0 });

	// Scores display
	go = scene->CreateGameObject();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	tr->SetColor(yellow);
	tr->SetText("Q: dot, W: energized, E: ghost, R: cherry");
	go->SetLocalPosition({ 200, 350, 0 });

	go = scene->CreateGameObject();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	tr->SetColor(yellow);
	auto scoreDisplayP1 = go->AddComponent<dae::ScoreDisplay>();
	go->SetLocalPosition({ 30, 350, 0 });

	go = scene->CreateGameObject();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	tr->SetColor(green);
	tr->SetText("A: dot, S: energized, D: ghost, F: cherry");
	go->SetLocalPosition({ 200, 430, 0 });

	go = scene->CreateGameObject();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	tr->SetColor(green);
	auto scoreDisplayP2 = go->AddComponent<dae::ScoreDisplay>();
	go->SetLocalPosition({ 30, 430, 0 });

	// CHARACTER
	go = scene->CreateGameObject();
	auto player1 = go->AddComponent<dae::TestCharacter>();
	player1->SetMaxLives(3);
	player1->AddObserver(livesDisplayP1);
	player1->AddObserver(scoreDisplayP1);

	go = scene->CreateGameObject();
	auto player2 = go->AddComponent<dae::TestCharacter>();
	player2->SetMaxLives(3);
	player2->AddObserver(livesDisplayP2);
	player2->AddObserver(scoreDisplayP2);

	// COMMANDS
	{
		using namespace dae;

		input.AddKeyboardCommand({ SDL_SCANCODE_1, ButtonState::Pressed }, std::make_shared<TestKill>(player1));
		input.AddKeyboardCommand({ SDL_SCANCODE_2, ButtonState::Pressed }, std::make_shared<TestKill>(player2));

		input.AddKeyboardCommand({ SDL_SCANCODE_Q, ButtonState::Pressed }, std::make_shared<TestEvent>(player1, GameEvents::DotCollected));
		input.AddKeyboardCommand({ SDL_SCANCODE_W, ButtonState::Pressed }, std::make_shared<TestEvent>(player1, GameEvents::EnergizerCollected));
		input.AddKeyboardCommand({ SDL_SCANCODE_E, ButtonState::Pressed }, std::make_shared<TestEvent>(player1, GameEvents::GhostKilled));
		input.AddKeyboardCommand({ SDL_SCANCODE_R, ButtonState::Pressed }, std::make_shared<TestEvent>(player1, GameEvents::CherryCollected));

		input.AddKeyboardCommand({ SDL_SCANCODE_A, ButtonState::Pressed }, std::make_shared<TestEvent>(player2, GameEvents::DotCollected));
		input.AddKeyboardCommand({ SDL_SCANCODE_S, ButtonState::Pressed }, std::make_shared<TestEvent>(player2, GameEvents::EnergizerCollected));
		input.AddKeyboardCommand({ SDL_SCANCODE_D, ButtonState::Pressed }, std::make_shared<TestEvent>(player2, GameEvents::GhostKilled));
		input.AddKeyboardCommand({ SDL_SCANCODE_F, ButtonState::Pressed }, std::make_shared<TestEvent>(player2, GameEvents::CherryCollected));

	}
}