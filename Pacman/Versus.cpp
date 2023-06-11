#include "Versus.h"
#include "Character.h"
#include "Ghost.h"
#include "PacmanEvents.h"
#include <stdexcept>
#include "Game.h"

pacman::Versus::Versus(dae::GameObject* pGameObject)
	: Gamemode(pGameObject)
	, m_pPlayer{ nullptr }
{
}

void pacman::Versus::Start()
{
	LoadLevel(m_Level);
}

void pacman::Versus::SkipLevel()
{
	const unsigned nrOffLevels{ 3 };
	++m_Level;
	m_Level = m_Level % nrOffLevels;
	LoadLevel(m_Level);

	for (auto& ghost : m_pGhosts)
		ghost->Reset();

	m_pPlayer->Reset();

	Notify(PEvents::LevelLoaded);
}

void pacman::Versus::AddPlayer(Character* player)
{
	if (player == nullptr)
		throw std::runtime_error("player is nullptr");

	m_pPlayer = player;
}

void pacman::Versus::OnNotify(unsigned event)
{
	Gamemode::OnNotify(event);

	switch (event)
	{
	case PEvents::AllItemsCollected:
		SkipLevel();
		break;
	case PEvents::PlayerOutOffLives:
		Game::GetInstance().EndGamemode();
		break;
	default:
		break;
	}
}
