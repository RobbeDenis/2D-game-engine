#pragma once
#include "Grid.h"

namespace pacman
{
	class GridAgent final
	{
	public:
		GridAgent(Grid* pGrid);

		void MoveDirection(const glm::ivec2& direction);
		const glm::ivec2& GetGridPosition() const;
		const glm::ivec2& GetDirection() const;
		const Coordinate& GetCoordinate() const;
		unsigned GetTag() const;

	private:
		friend Grid;
		void SetCoordinate(const Coordinate& coordinate);
		void SetGridPosition(const glm::ivec2& position);

		glm::ivec2 m_GridPosition;
		glm::ivec2 m_Direction;
		Coordinate m_Coordinate;
		float m_MovementSpeed;
		Grid* m_pGrid;
	};
}