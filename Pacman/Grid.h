#pragma once
#include <Component.h>

namespace pacman
{
	class Grid : public dae::Component
	{
	public:
		Grid(dae::GameObject* pGameObject);

		void Initialize(unsigned colums, unsigned rows, unsigned cellSize);
		void Loaded() override;

		unsigned GetColums() const { return m_Colums; }
		unsigned GetRows() const { return m_Rows; }
		unsigned GetCellSize() const { return m_CellSize; }

	private:
		unsigned m_Colums;
		unsigned m_Rows;
		unsigned m_CellSize;
	};
}