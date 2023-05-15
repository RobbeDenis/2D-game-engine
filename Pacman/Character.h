#pragma once
#include <Component.h>
#include "Grid.h"

namespace pacman
{
	class Grid;
	class GridAgent;
	class Character : public dae::Component
	{
	public:
		Character(dae::GameObject* pGameObject);

		void Loaded() override;
		void Update() override;

		void Move(int x, int y);
		void InitGridAgent(Grid* pGrid, const Coordinate& coordinate);

	private:
		glm::ivec2 m_Direction;
		GridAgent* m_pAgent;
	};
}