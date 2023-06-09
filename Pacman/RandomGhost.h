#pragma once
#include "Ghost.h"

namespace pacman
{
	class RandomGhost final : public Ghost
	{
	public:
		RandomGhost(dae::GameObject* pGameObject);
		void Loaded() override;

		void Reset() override;
		void Scare() override;
		void Kill() override;
		bool CanKill() const override;

	private:
		enum State
		{
			Start = 0,
			Wander = 1,
			Run = 2,
			Dead = 3,
			Blink = 4
		};

		void EnterStart();
		void UpdateStart();
		void EnterWander();
		void UpdateWander();
		void UpdateDead();

		void EnterRun();
		void UpdateRun();
		void ExitRun();
		void EnterBlink();
		void UpdateBlink();

		void UpdateDirection();
		unsigned GetRandomInt(unsigned min, unsigned max);

		Coordinate m_PrevCoordinate;
		float m_MaxRunTime;
		float m_RunTime;
		float m_MaxBlinkTime;
		float m_BlinkTime;
	};
}