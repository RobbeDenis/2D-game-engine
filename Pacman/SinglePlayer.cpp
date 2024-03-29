#include "SinglePlayer.h"
#include "Character.h"
#include "Ghost.h"
#include <stdexcept>
#include "PacmanEvents.h"
#include <iostream>
#include "Game.h"
#include "SceneIds.h"


pacman::SinglePlayer::SinglePlayer(dae::GameObject* pGameObject)
	: Gamemode(pGameObject)
	, m_pPlayer{ nullptr }
{
}

void pacman::SinglePlayer::Start()
{
	Gamemode::Start();
	LoadLevel(m_Level);
}

void pacman::SinglePlayer::SkipLevel()
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

void pacman::SinglePlayer::AddPlayer(Character* player)
{
	if (player == nullptr)
		throw std::runtime_error("player is nullptr");

	m_pPlayer = player;
}

void pacman::SinglePlayer::OnNotify(unsigned event)
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
