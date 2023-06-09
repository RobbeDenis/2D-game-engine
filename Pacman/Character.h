#pragma once
#include <Component.h>
#include <StateMachine.h>
#include "Grid.h"
#include "GridAgent.h"

namespace pacman
{
	class Grid;
	class GridAgent;
	class Character : public dae::Component, public dae::StateMachine
	{
	public:
		Character(dae::GameObject* pGameObject);

		virtual void Loaded() override;
		virtual void Update() override;
		virtual void Reset() {};

		virtual void Move(int x, int y);
		void InitGridAgent(Grid* pGrid, const Coordinate& coordinate);

	protected:
		Coordinate m_SpawnPoint;
		glm::ivec2 m_Direction;
		GridAgent* m_pAgent;
	};
}