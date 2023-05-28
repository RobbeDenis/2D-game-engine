#include "GameplayManager.h"
#include "PacmanEvents.h"
#include "Ghost.h"

pacman::GameplayManager::GameplayManager(dae::GameObject* pGameObject)
	: Component(pGameObject)
	, m_pGhosts{ }
{
}

void pacman::GameplayManager::OnNotify(unsigned event)
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

void pacman::GameplayManager::PowerCollected()
{
	for (Ghost* ghost : m_pGhosts)
		ghost->Scare();
}

void pacman::GameplayManager::AddGhost(Ghost* ghost)
{
	m_pGhosts.push_back(ghost);
}