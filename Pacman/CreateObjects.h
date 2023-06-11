#pragma once

#include <SceneManager.h>
#include <SpriteRenderer.h>
#include <Collider.h>

#include "Grid.h"
#include "Ghost.h"
#include "Pacman.h"
#include "FPSCounter.h"
#include "GridRenderer.h"
#include "ScoreDisplay.h"
#include "LivesDisplay.h"
#include "LivesRender.h"
#include "Highscore.h"
#include <Animator.h>

dae::GameObject* CreatePacman(dae::Scene* const scene, const std::string& texture, pacman::Grid* grid, const pacman::Coordinate& c)
{
	auto go{ scene->CreateGameObject() };
	auto sprite{ go->AddComponent<dae::SpriteRenderer>() };
	sprite->SetTexture(texture);
	auto pacman{ go->AddComponent<pacman::Pacman>() };
	pacman->InitGridAgent(grid, c);
	go->AddComponent<dae::Collider>();
	go->AddComponent<dae::Animator>();

	return go;
}

pacman::Ghost* CreateGhost(dae::Scene* const scene, const std::string& texture, pacman::Grid* grid, const pacman::Coordinate& c, dae::GameObject* target, const glm::ivec2& chaseAxis)
{
	auto go{ scene->CreateGameObject() };
	auto sprite{ go->AddComponent<dae::SpriteRenderer>() };
	sprite->SetTexture(texture);
	auto ghost{ go->AddComponent<pacman::Ghost>() };
	ghost->InitGridAgent(grid, c);
	ghost->SetTarget(target);
	ghost->SetChaseAxis(chaseAxis);
	go->AddComponent<dae::Collider>();

	return ghost;
}

dae::FPSCounter* CreateFPS(dae::Scene* const scene)
{
	auto go{ scene->CreateGameObject() };
	auto font2 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto tr2 = go->AddComponent<dae::TextRenderer>();
	tr2->SetText("FPS");
	tr2->SetFont(font2);
	tr2->SetColor({ 0, 255, 0 });
	return go->AddComponent<dae::FPSCounter>();
}

pacman::Grid* CreateGrid(dae::Scene* const scene, pacman::Gamemode* gamemode, int x, int y)
{
	auto go{ scene->CreateGameObject() };
	auto grid = go->AddComponent<pacman::Grid>();
	auto gridRender = go->AddComponent<pacman::GridRenderer>();
	gamemode->AddObserver(gridRender);
	grid->AddObserver(gridRender);
	grid->AddObserver(gamemode);
	go->SetLocalPosition(x, y);
	gamemode->AssignGrid(grid);

	return grid;
}

pacman::ScoreDisplay* CreateScoreDisplay(dae::Scene* const scene, const SDL_Color& color, int x, int y)
{
	auto go{ scene->CreateGameObject() };
	auto tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22));
	tr->SetColor(color);
	tr->SetText("SCORE");
	go->SetLocalPosition(x, y);
	go = go->AddChild();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 19));
	tr->SetColor(color);
	auto score = go->AddComponent<pacman::ScoreDisplay>();
	go->SetLocalPosition(20, 19);

	return score;
}

pacman::Highscore* CreateHighscore(dae::Scene* const scene, const SDL_Color& color, int x, int y)
{
	auto go{ scene->CreateGameObject() };
	auto tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22));
	tr->SetColor(color);
	tr->SetText("HIGH SCORE");
	go->SetLocalPosition(x, y);
	go = go->AddChild();
	tr = go->AddComponent<dae::TextRenderer>();
	tr->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 19));
	tr->SetColor(color);
	auto score = go->AddComponent<pacman::Highscore>();
	go->SetLocalPosition(20, 19);

	return score;
}

pacman::LivesDisplay* CreateLivesDisplay(dae::Scene* const scene, const std::string& texture, pacman::Gamemode* gamemode, int x, int y)
{
	auto go{ scene->CreateGameObject() };
	auto lives = go->AddComponent<pacman::LivesDisplay>();
	auto lr = go->AddComponent<pacman::LivesRender>();
	lr->SetLivesDisplay(lives);
	lr->SetTexture(texture);
	go->SetLocalPosition(x, y);
	lives->AddObserver(gamemode);

	return lives;
}