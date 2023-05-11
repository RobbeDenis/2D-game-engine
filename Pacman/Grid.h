#pragma once
#include <Component.h>
#include <vector>
#include <string>

namespace pacman
{
	enum CellType
	{
		Empty = 0,
		Wall = 1
	};

	class Grid : public dae::Component
	{
	public:
		Grid(dae::GameObject* pGameObject);

		void LoadFromFile(unsigned colums, unsigned rows, unsigned cellSize, const std::string& filename);
		void Loaded() override;

		unsigned GetCellData(unsigned x, unsigned y) const { return m_Cells[x][y]; }
		unsigned GetColums() const { return m_Colums; }
		unsigned GetRows() const { return m_Rows; }
		unsigned GetCellSize() const { return m_CellSize; }

		void PrintGrid() const;

	private:
		std::vector<std::vector<unsigned>> m_Cells;
		unsigned m_Colums;
		unsigned m_Rows;
		unsigned m_CellSize;
	};
}