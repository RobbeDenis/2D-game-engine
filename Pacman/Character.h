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

		virtual void Loaded() override;
		virtual void Update() override;

		virtual void Move(int x, int y);
		void InitGridAgent(Grid* pGrid, const Coordinate& coordinate);

	protected:
		glm::ivec2 m_Direction;
		GridAgent* m_pAgent;
	};
}