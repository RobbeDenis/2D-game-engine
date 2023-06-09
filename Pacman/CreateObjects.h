#pragma once

#include <SceneManager.h>
#include <SpriteRenderer.h>
#include <Collider.h>

#include "Grid.h"
#include "Ghost.h"
#include "Pacman.h"

dae::GameObject* CreatePacman(dae::Scene* const scene, const std::string& texture, pacman::Grid* grid, const pacman::Coordinate& c)
{
	auto go{ scene->CreateGameObject() };
	auto sprite{ go->AddComponent<dae::SpriteRenderer>() };
	sprite->SetTexture(texture);
	auto pacman{ go->AddComponent<pacman::Pacman>() };
	pacman->InitGridAgent(grid, c);
	go->AddComponent<dae::Collider>();

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