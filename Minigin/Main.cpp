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

void load()
{
	dae::Scene* scene = dae::SceneManager::GetInstance().CreateScene("Demo");

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

	// IMGUI
	// DONT FORGET TO IMPLEMENT RENDER ORDER
	go = scene->CreateGameObject();
	go->AddComponent<dae::ImGuiRenderer>();
	go->AddComponent<dae::TrashTheCash>();

	// TEST
	go = scene->CreateGameObject();
	go->SetLocalPosition(250, 50);
	go->AddComponent<dae::TestComp>();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(font);
	tr->SetText("PARENT");

	auto child = go->AddChild("left");
	child->SetLocalPosition(-100, 20);
	tr = child->AddComponent<dae::TextRenderer>();
	tr->SetFont(font);
	tr->SetText("left");
	auto otherChild = child->AddChild("left child");
	otherChild->SetLocalPosition(-100, 0);
	tr = otherChild->AddComponent<dae::TextRenderer>();
	tr->SetFont(font);
	tr->SetText("left child");

	child = go->AddChild("right");
	child->SetLocalPosition(100, 20);
	tr = child->AddComponent<dae::TextRenderer>();
	tr->SetFont(font);
	tr->SetText("right");
	otherChild = child->AddChild("right child");
	otherChild->SetLocalPosition(100, 0);
	tr = otherChild->AddComponent<dae::TextRenderer>();
	tr->SetFont(font);
	tr->SetText("right child");

	child = go->AddChild("2");
	child->SetLocalPosition(-100, 40);
	tr = child->AddComponent<dae::TextRenderer>();
	tr->SetFont(font);
	tr->SetText("2");
	otherChild = child->AddChild("2 child");
	otherChild->SetLocalPosition(-100, 0);
	tr = otherChild->AddComponent<dae::TextRenderer>();
	tr->SetFont(font);
	tr->SetText("2 child");

	child = go->AddChild("3");
	child->SetLocalPosition(100, 40);
	tr = child->AddComponent<dae::TextRenderer>();
	tr->SetFont(font);
	tr->SetText("3");
	otherChild = child->AddChild("3 child");
	otherChild->SetLocalPosition(100, 0);
	tr = otherChild->AddComponent<dae::TextRenderer>();
	tr->SetFont(font);
	tr->SetText("3 child");
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}