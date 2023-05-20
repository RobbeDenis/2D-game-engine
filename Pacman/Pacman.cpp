#include "Pacman.h"
#include "GridAgent.h"
#include <iostream>
#include "PacmanEvents.h"

pacman::Pacman::Pacman(dae::GameObject* pGameObject)
	: Character(pGameObject)
{

}

void pacman::Pacman::Update()
{
	Character::Update();

	switch (m_pAgent->Pickup())
	{
	case CellType::Dot:
		Notify(PEvents::CDot);
		break;
	case CellType::Power:
		Notify(PEvents::CPower);
		break;
	case CellType::Cherry:
		Notify(PEvents::CFruit);
		break;
	case CellType::Strawberry:
		Notify(PEvents::CFruit);
		break;
	case CellType::Melon:
		Notify(PEvents::CFruit);
		break;
	default:
		break;
	}
}
