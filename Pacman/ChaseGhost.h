#pragma once
#include "Ghost.h"

namespace pacman
{
	class ChaseGhost final : public Ghost
	{
	public:
		ChaseGhost(dae::GameObject* pGameObject);
		void Loaded() override;

		void SetTarget(dae::GameObject* pTarget);
		void SetChaseAxis(int horizontal, int vertical);

	private:
		enum State
		{
			Start = 0,
			Chase = 1,
			Dead = 2
		};

		void UpdateStart();
		void UpdateChase();
		void UpdateDead();

		void UpdateDirection();
		unsigned GetRandomInt(unsigned min, unsigned max);

		glm::ivec2 m_ChaseAxis;
		Coordinate m_PrevCoordinate;
		dae::GameObject* m_pTarget;
	};
}