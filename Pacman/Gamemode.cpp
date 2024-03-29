#include "Gamemode.h"
#include "Ghost.h"
#include "PacmanEvents.h"
#include <SDLSoundSystem.h>
#include "PacmanSounds.h"

pacman::Gamemode::Gamemode(dae::GameObject* pGameObject)
	: Component(pGameObject)
	, m_pGhosts{ }
	, m_pGrid{ }
	, m_Level{ }
{
}

void pacman::Gamemode::Start()
{
	dae::SoundSystemLocator::GetSoundSystem().Play(PacmanSounds::GameStart, 0.6f);
}

void pacman::Gamemode::OnNotify(unsigned event)
{
	switch (event)
	{
	case PEvents::CPower:
		PowerCollected();
		break;
	default:
		break;
	}
}

void pacman::Gamemode::AddGhost(Ghost* ghost)
{
	m_pGhosts.push_back(ghost);
}

void pacman::Gamemode::AssignGrid(Grid* grid)
{
	if (grid == nullptr)
		return;

	m_pGrid = grid;
}

void pacman::Gamemode::LoadLevel(unsigned level)
{
	std::string fileName{ "Level_" + std::to_string(level) + ".lvl" };
	m_pGrid->LoadFromFile(fileName);
}

void pacman::Gamemode::PowerCollected()
{
	for (Ghost* ghost : m_pGhosts)
		ghost->Scare();
}
