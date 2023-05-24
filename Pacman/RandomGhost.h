#pragma once
#include "Character.h"

namespace pacman
{
	class RandomGhost final : public Character
	{
	public:
		RandomGhost(dae::GameObject* pGameObject);
		void Loaded() override;

	private:
		enum State
		{
			Start = 0,
			Wander = 1,
			Dead = 2
		};

		void EnterStart();
		void UpdateStart();
		void UpdateWander();
		void UpdateDead();

		void UpdateDirection();
		unsigned GetRandomInt(unsigned min, unsigned max);

		Coordinate m_PrevCoordinate;
	};
}