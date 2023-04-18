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
#include "TestCharacter.h"

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
	tr->SetFont(font);
	tr->SetColor({ 0, 255, 0 });
	go->AddComponent<dae::FPSCounter>();

	// CHARACTER
	go = scene->CreateGameObject();
	auto player = go->AddComponent<dae::TestCharacter>();
	player->SetMaxLives(3);

	// COMMANDS
	{
		using namespace dae;

		input.AddKeyboardCommand({ SDL_SCANCODE_1, ButtonState::Pressed }, std::make_shared<TestKill>(player));
	}
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}