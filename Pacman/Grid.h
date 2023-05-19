#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace pacman
{
	struct Coordinate
	{
		unsigned x;
		unsigned y;
	};

	enum CellType
	{
		Empty = 0,
		Wall = 1,
		Dot = 2,
		Power = 3
	};

	class GridAgent;
	class Grid : public dae::Component
	{
	public:
		Grid(dae::GameObject* pGameObject);

		void LoadFromFile(unsigned colums, unsigned rows, unsigned cellSize, const std::string& filename);
		void Loaded() override;

		GridAgent* CreateAgent(const Coordinate& coordinate);
		void MoveAgentInDirection(GridAgent* pAgent, float speed, const glm::ivec2& newDirection);
		Coordinate GetCoordinateFromPosition(const glm::ivec2& position);

		unsigned GetCellData(unsigned x, unsigned y) const { return m_Cells[x][y]; }
		unsigned GetColums() const { return m_Colums; }
		unsigned GetRows() const { return m_Rows; }
		unsigned GetCellSize() const { return m_CellSize; }

		void PrintGrid() const;
		const auto& GetAgents() const { return m_pAgents; }

	private:
		glm::ivec2 CalculateCellPosition(const Coordinate& coordinate);
		bool CanTurn(const glm::ivec2& pos, const glm::ivec2& sumDir);

		std::vector<std::vector<unsigned>> m_Cells;
		std::vector<std::unique_ptr<GridAgent>> m_pAgents;
		unsigned m_Colums;
		unsigned m_Rows;
		unsigned m_CellSize;
		unsigned m_Offset;
	};
}