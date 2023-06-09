#include "GridAgent.h"
#include <iostream>

pacman::GridAgent::GridAgent(Grid* pGrid)
	: m_pGrid{ pGrid }
	, m_Coordinate{  }
	, m_GridPosition{  }
	, m_MovementSpeed{ 70.f }
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

unsigned pacman::GridAgent::Pickup()
{
	return m_pGrid->Pickup(m_Coordinate);
}

unsigned pacman::GridAgent::LookAt(const Coordinate& c) const
{
	return m_pGrid->GetCellData(c.y, c.x);
}

pacman::Grid* pacman::GridAgent::GetGrid() const
{
	return m_pGrid;
}

void pacman::GridAgent::SetMovementSpeed(float speed)
{
	m_MovementSpeed = speed;
}

void pacman::GridAgent::Reset(const Coordinate& coordinate)
{
	SetCoordinate(coordinate);
	SetGridPosition(m_pGrid->CalculateCellPosition(coordinate));
	m_Direction = { 0,0 };
}