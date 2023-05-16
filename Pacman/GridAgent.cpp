#include "GridAgent.h"

pacman::GridAgent::GridAgent(Grid* pGrid)
	: m_pGrid{ pGrid }
	, m_Coordinate{  }
	, m_GridPosition{  }
	, m_MovementSpeed{ 150.f }
	, m_Direction{  }
{

}

void pacman::GridAgent::MoveDirection(const glm::ivec2& direction)
{
	m_pGrid->MoveAgentInDirection(this, m_MovementSpeed, direction);
}

void pacman::GridAgent::SetCoordinate(const Coordinate& coordinate)
{
	m_Coordinate = coordinate;
}

void pacman::GridAgent::SetGridPosition(const glm::ivec2& position)
{
	m_GridPosition = position;
}

void pacman::GridAgent::SetDirection(const glm::ivec2& direction)
{
	m_Direction = direction;
}

const glm::ivec2& pacman::GridAgent::GetGridPosition() const
{
	return m_GridPosition;
}

const pacman::Coordinate& pacman::GridAgent::GetCoordinate() const
{
	return m_Coordinate;
}

const glm::ivec2& pacman::GridAgent::GetDirection() const
{
	return m_Direction;
}