#include "Pacman.h"
#include "GridAgent.h"
#include <iostream>

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
		std::cout << "Dot\n";
		break;
	case CellType::Power:
		std::cout << "Power\n";
		break;
	case CellType::Cherry:
		std::cout << "Cherry\n";
		break;
	case CellType::Strawberry:
		std::cout << "Strawberry\n";
		break;
	case CellType::Melon:
		std::cout << "Melon\n";
		break;
	default:
		break;
	}
}
