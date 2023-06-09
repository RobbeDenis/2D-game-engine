#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <Subject.h>

namespace pacman
{
	struct Coordinate
	{
		unsigned x;
		unsigned y;

		bool operator==(const Coordinate& c)
		{
			return x == c.x && y == c.y;
		}
	};

	enum CellType
	{
		Empty = 0,
		Wall = 1,
		Dot = 2,
		Power = 3,
		Cherry = 4,
		Strawberry = 5,
		Melon = 6
	};

	class GridAgent;
	class Grid : public dae::Component, public dae::Subject
	{
	public:
		Grid(dae::GameObject* pGameObject);

		void LoadFromFile(const std::string& filename);
		void Loaded() override;

		GridAgent* CreateAgent(const Coordinate& coordinate);
		void MoveAgentInDirection(GridAgent* pAgent, float speed, const glm::ivec2& newDirection);
		Coordinate GetCoordinateFromPosition(const glm::ivec2& position);
		glm::ivec2 CalculateCellPosition(const Coordinate& coordinate);

		unsigned Pickup(const Coordinate& c);

		unsigned GetCellData(unsigned r, unsigned c) const;
		unsigned GetColums() const { return m_Colums; }
		unsigned GetRows() const { return m_Rows; }
		unsigned GetCellSize() const { return m_CellSize; }
		const auto& GetAgents() const { return m_pAgents; }

		void PrintGrid() const;

	private:
		bool CanTurn(const glm::ivec2& pos, const glm::ivec2& sumDir);

		std::vector<std::vector<unsigned>> m_Cells;
		std::vector<std::unique_ptr<GridAgent>> m_pAgents;
		unsigned m_Colums;
		unsigned m_Rows;
		unsigned m_CellSize;
		unsigned m_Offset;
	};
}