#include "Character.h"
#include "GameObject.h"
#include "GridAgent.h"

pacman::Character::Character(dae::GameObject* pGameObject)
	: dae::Component(pGameObject)
	, m_pAgent{ nullptr }
	, m_Direction{  }
{
}

void pacman::Character::Loaded()
{
	const glm::ivec2 pos = m_pAgent->GetGridPosition();
	GetGameObject()->SetLocalPosition(pos.x, pos.y);
}

void pacman::Character::Update()
{
	m_pAgent->MoveDirection(m_Direction);
	const glm::ivec2 newPos{ m_pAgent->GetGridPosition() };
	GetGameObject()->SetLocalPosition(newPos.x, newPos.y);
}

void pacman::Character::Move(int x, int y)
{
	m_Direction.x = x;
	m_Direction.y = y;

	std::cout << x << ", " << y << "\n";
}

void pacman::Character::InitGridAgent(Grid* pGrid, const Coordinate& coordinate)
{
	m_pAgent = pGrid->CreateAgent(coordinate);
}