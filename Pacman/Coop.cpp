#include "Coop.h"
#include "Ghost.h"
#include "Character.h"
#include "PacmanEvents.h"
#include "Game.h"

pacman::Coop::Coop(dae::GameObject* pGameObject)
	: Gamemode(pGameObject)
	, m_pPlayer1{ nullptr }
	, m_pPlayer2{ nullptr }
{
}

void pacman::Coop::Start()
{
	LoadLevel(m_Level);
}

void pacman::Coop::SkipLevel()
{
	const unsigned nrOffLevels{ 3 };
	++m_Level;
	m_Level = m_Level % nrOffLevels;
	LoadLevel(m_Level);

	for (auto& ghost : m_pGhosts)
		ghost->Reset();

	m_pPlayer1->Reset();
	//m_pPlayer2->Reset();

	Notify(PEvents::LevelLoaded);
}

void pacman::Coop::OnNotify(unsigned event)
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

void pacman::Coop::AddPlayer1(Character* p)
{
	m_pPlayer1 = p;
}

void pacman::Coop::AddPlayer2(Character* p)
{
	m_pPlayer2 = p;
}
