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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::SpriteRenderer>().lock()->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::SpriteRenderer>().lock()->SetTexture("logo.tga");
	go->SetLocalPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto tr = go->AddComponent<dae::TextRenderer>().lock();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	tr->SetText("Programming 4 Assignment");
	tr->SetFont(font);
	go->SetLocalPosition(90, 0);
	scene.Add(go);

	// FPS
	go = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	tr = go->AddComponent<dae::TextRenderer>().lock();
	tr->SetFont(font);
	tr->SetColor({ 0, 255, 0 });
	go->AddComponent<dae::FPSCounter>();
	scene.Add(go);

	// ROTATION
	go = std::make_shared<dae::GameObject>();
	go->SetLocalPosition(320, 300);

	auto redGhost = go->AddChild().lock();
	redGhost->AddComponent<dae::SpriteRenderer>().lock()->SetTexture("RedGhost.png");
	auto rotate = redGhost->AddComponent<dae::RotateParent>().lock();
	rotate->SetSpeed(1.5f);
	redGhost->SetLocalPosition(32, 0);

	auto CyanGhost = redGhost->AddChild().lock();
	rotate = CyanGhost->AddComponent<dae::RotateParent>().lock();
	rotate->SetDirection(-1);
	rotate->SetSpeed(3.f);
	CyanGhost->AddComponent<dae::SpriteRenderer>().lock()->SetTexture("CyanGhost.png");
	CyanGhost->SetLocalPosition(32, 0);

	scene.Add(go);

	// TEST
	//go = std::make_shared<dae::GameObject>();
	//go->SetLocalPosition(250, 50);
	//go->AddComponent<dae::TestComp>();
	//tr = go->AddComponent<dae::TextRenderer>().lock();
	//tr->SetFont(font);
	//tr->SetText("PARENT");

	//auto child = go->AddChild("left").lock();
	//child->SetLocalPosition(-100, 20);
	//tr = child->AddComponent<dae::TextRenderer>().lock();
	//tr->SetFont(font);
	//tr->SetText("left");
	//auto otherChild = child->AddChild("left child").lock();
	//otherChild->SetLocalPosition(-100, 0);
	//tr = otherChild->AddComponent<dae::TextRenderer>().lock();
	//tr->SetFont(font);
	//tr->SetText("left child");

	//child = go->AddChild("right").lock();
	//child->SetLocalPosition(100, 20);
	//tr = child->AddComponent<dae::TextRenderer>().lock();
	//tr->SetFont(font);
	//tr->SetText("right");
	//otherChild = child->AddChild("right child").lock();
	//otherChild->SetLocalPosition(100, 0);
	//tr = otherChild->AddComponent<dae::TextRenderer>().lock();
	//tr->SetFont(font);
	//tr->SetText("right child");

	//child = go->AddChild("2").lock();
	//child->SetLocalPosition(-100, 40);
	//tr = child->AddComponent<dae::TextRenderer>().lock();
	//tr->SetFont(font);
	//tr->SetText("2");
	//otherChild = child->AddChild("2 child").lock();
	//otherChild->SetLocalPosition(-100, 0);
	//tr = otherChild->AddComponent<dae::TextRenderer>().lock();
	//tr->SetFont(font);
	//tr->SetText("2 child");

	//child = go->AddChild("3").lock();
	//child->SetLocalPosition(100, 40);
	//tr = child->AddComponent<dae::TextRenderer>().lock();
	//tr->SetFont(font);
	//tr->SetText("3");
	//otherChild = child->AddChild("3 child").lock();
	//otherChild->SetLocalPosition(100, 0);
	//tr = otherChild->AddComponent<dae::TextRenderer>().lock();
	//tr->SetFont(font);
	//tr->SetText("3 child");

	//scene.Add(go);
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}