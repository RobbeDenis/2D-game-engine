#include "Character.h"
#include "GameObject.h"
#include "GridAgent.h"

pacman::Character::Character(dae::GameObject* pGameObject)
	: dae::Component(pGameObject)
	, StateMachine()
	, m_pAgent{ nullptr }
	, m_Direction{ }
{
}

void pacman::Character::Loaded()
{
	const glm::ivec2 pos = m_pAgent->GetGridPosition();
	GetGameObject()->SetLocalPosition(pos.x, pos.y);
}

void pacman::Character::Update()
{
	UpdateState();
}

void pacman::Character::Move(int x, int y)
{
	m_Direction.x = x;
	m_Direction.y = y;
}

void pacman::Character::InitGridAgent(Grid* pGrid, const Coordinate& coordinate)
{
	m_pAgent = pGrid->CreateAgent(coordinate);
}