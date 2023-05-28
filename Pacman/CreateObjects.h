#pragma once

#include <SceneManager.h>
#include <SpriteRenderer.h>
#include <Collider.h>

#include "Grid.h"
#include "ChaseGhost.h"
#include "RandomGhost.h"
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

pacman::ChaseGhost* CreateChaseGhost(dae::Scene* const scene, const std::string& texture, pacman::Grid* grid, const pacman::Coordinate& c, dae::GameObject* target, const glm::ivec2& chaseAxis)
{
	auto go{ scene->CreateGameObject() };
	auto sprite{ go->AddComponent<dae::SpriteRenderer>() };
	sprite->SetTexture(texture);
	auto ghost{ go->AddComponent<pacman::ChaseGhost>() };
	ghost->InitGridAgent(grid, c);
	ghost->SetTarget(target);
	ghost->SetChaseAxis(chaseAxis);
	go->AddComponent<dae::Collider>();

	return ghost;
}

pacman::RandomGhost* CreateRandomGhost(dae::Scene* const scene, const std::string& texture, pacman::Grid* grid, const pacman::Coordinate& c)
{
	auto go{ scene->CreateGameObject() };
	auto sprite{ go->AddComponent<dae::SpriteRenderer>() };
	sprite->SetTexture(texture);
	auto ghost = go->AddComponent<pacman::RandomGhost>();
	ghost->InitGridAgent(grid, c);
	go->AddComponent<dae::Collider>();

	return ghost;
}