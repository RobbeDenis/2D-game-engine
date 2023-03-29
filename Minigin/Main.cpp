#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
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

void load()
{
	auto& input = dae::InputManager::GetInstance();
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
	tr->SetFont(font);
	tr->SetColor({ 0, 255, 0 });
	go->AddComponent<dae::FPSCounter>();

	// COMMANDS
	go = scene->CreateGameObject();
	go->AddComponent<dae::SpriteRenderer>()->SetTexture("RedGhost.png");
	dae::Movement* redMovement = go->AddComponent<dae::Movement>();
	go->SetLocalPosition(270, 300);

	go = scene->CreateGameObject();
	go->AddComponent<dae::SpriteRenderer>()->SetTexture("CyanGhost.png");
	dae::Movement* blueMovement = go->AddComponent<dae::Movement>();
	blueMovement->SetMovementSpeed(200.f);
	go->SetLocalPosition(350, 300);

	{
		using namespace dae;
		input.AddXBoxController(0);

		input.AddControllerCommand({ xbox::XBoxButton::ButtonLeft, ButtonState::Down }, std::make_shared<TestMove>(-1, 0, redMovement));
		input.AddControllerCommand({ xbox::XBoxButton::ButtonDown, ButtonState::Down }, std::make_shared<TestMove>(0, 1, redMovement));
		input.AddControllerCommand({ xbox::XBoxButton::ButtonRight, ButtonState::Down }, std::make_shared<TestMove>(1, 0, redMovement));
		input.AddControllerCommand({ xbox::XBoxButton::ButtonUp, ButtonState::Down }, std::make_shared<TestMove>(0, -1, redMovement));

		input.AddKeyboardCommand({ SDL_SCANCODE_W, ButtonState::Down }, std::make_shared<TestMove>(0, -1, blueMovement));
		input.AddKeyboardCommand({ SDL_SCANCODE_S, ButtonState::Down }, std::make_shared<TestMove>(0, 1, blueMovement));
		input.AddKeyboardCommand({ SDL_SCANCODE_A, ButtonState::Down }, std::make_shared<TestMove>(-1, 0, blueMovement));
		input.AddKeyboardCommand({ SDL_SCANCODE_D, ButtonState::Down }, std::make_shared<TestMove>(1, 0, blueMovement));

		// For testing other button states
		input.AddKeyboardCommand({ SDL_SCANCODE_SPACE, ButtonState::Pressed }, std::make_shared<TestPrint>("SPACE Pressed"));
		input.AddKeyboardCommand({ SDL_SCANCODE_E, ButtonState::Released }, std::make_shared<TestPrint>("E Released"));
		input.AddControllerCommand({ xbox::XBoxButton::RightBumper, ButtonState::Released }, std::make_shared<TestPrint>("RB Released"));
		input.AddControllerCommand({ xbox::XBoxButton::Back, ButtonState::Pressed }, std::make_shared<TestPrint>("Back Pressed"));
	}

	//// TEST
	//go = scene->CreateGameObject();
	//go->SetLocalPosition(250, 50);
	//go->AddComponent<dae::TestComp>();
	//tr = go->AddComponent<dae::TextRenderer>();
	//tr->SetFont(font);
	//tr->SetText("PARENT");

	//auto child = go->AddChild("left");
	//child->SetLocalPosition(-100, 20);
	//tr = child->AddComponent<dae::TextRenderer>();
	//tr->SetFont(font);
	//tr->SetText("left");
	//auto otherChild = child->AddChild("left child");
	//otherChild->SetLocalPosition(-100, 0);
	//tr = otherChild->AddComponent<dae::TextRenderer>();
	//tr->SetFont(font);
	//tr->SetText("left child");

	//child = go->AddChild("right");
	//child->SetLocalPosition(100, 20);
	//tr = child->AddComponent<dae::TextRenderer>();
	//tr->SetFont(font);
	//tr->SetText("right");
	//otherChild = child->AddChild("right child");
	//otherChild->SetLocalPosition(100, 0);
	//tr = otherChild->AddComponent<dae::TextRenderer>();
	//tr->SetFont(font);
	//tr->SetText("right child");

	//child = go->AddChild("2");
	//child->SetLocalPosition(-100, 40);
	//tr = child->AddComponent<dae::TextRenderer>();
	//tr->SetFont(font);
	//tr->SetText("2");
	//otherChild = child->AddChild("2 child");
	//otherChild->SetLocalPosition(-100, 0);
	//tr = otherChild->AddComponent<dae::TextRenderer>();
	//tr->SetFont(font);
	//tr->SetText("2 child");

	//child = go->AddChild("3");
	//child->SetLocalPosition(100, 40);
	//tr = child->AddComponent<dae::TextRenderer>();
	//tr->SetFont(font);
	//tr->SetText("3");
	//otherChild = child->AddChild("3 child");
	//otherChild->SetLocalPosition(100, 0);
	//tr = otherChild->AddComponent<dae::TextRenderer>();
	//tr->SetFont(font);
	//tr->SetText("3 child");
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}