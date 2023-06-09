#pragma once
#include "Grid.h"

namespace pacman
{
	class GridAgent final
	{
	public:
		GridAgent(Grid* pGrid);

		void Reset(const Coordinate& coordinate);
		void MoveDirection(const glm::ivec2& direction);
		const glm::ivec2& GetGridPosition() const;
		const glm::ivec2& GetDirection() const;
		const Coordinate& GetCoordinate() const;
		unsigned Pickup();
		unsigned LookAt(const Coordinate& c) const;
		Grid* GetGrid() const;
		void SetMovementSpeed(float speed);

	private:
		friend Grid;
		void SetCoordinate(const Coordinate& coordinate);
		void SetGridPosition(const glm::ivec2& position);
		void SetDirection(const glm::ivec2& direction);

		glm::ivec2 m_GridPosition;
		glm::ivec2 m_Direction;
		Coordinate m_Coordinate;
		float m_MovementSpeed;
		Grid* m_pGrid;
	};
}