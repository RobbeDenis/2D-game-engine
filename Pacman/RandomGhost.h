#pragma once
#include "Ghost.h"

namespace pacman
{
	class RandomGhost final : public Ghost
	{
	public:
		RandomGhost(dae::GameObject* pGameObject);
		void Loaded() override;

		void Scare() override;

	private:
		enum State
		{
			Start = 0,
			Wander = 1,
			Run = 2,
			Dead = 3
		};

		void EnterStart();
		void UpdateStart();
		void UpdateWander();
		void UpdateDead();

		void EnterRun();
		void UpdateRun();
		void ExitRun();

		void UpdateDirection();
		unsigned GetRandomInt(unsigned min, unsigned max);

		Coordinate m_PrevCoordinate;
	};
}