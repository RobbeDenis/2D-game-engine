#pragma once
#include "Ghost.h"

namespace pacman
{
	class ChaseGhost final : public Ghost
	{
	public:
		ChaseGhost(dae::GameObject* pGameObject);
		void Loaded() override;

		void Scare() override;
		void Kill() override;
		bool CanKill() const override;
		void SetTarget(dae::GameObject* pTarget);
		void SetChaseAxis(const glm::ivec2& axis);

	private:
		enum State
		{
			Start = 0,
			Chase = 1,
			Run = 2,
			Dead = 3,
			Blink = 4
		};

		void UpdateStart();
		void UpdateDead();
		void EnterChase();
		void UpdateChase();

		void EnterRun();
		void UpdateRun();
		void EnterBlink();
		void UpdateBlink();

		void UpdateDirection();
		void UpdateRunDirection();
		unsigned GetRandomInt(unsigned min, unsigned max);

		glm::ivec2 m_ChaseAxis;
		Coordinate m_PrevCoordinate;
		dae::GameObject* m_pTarget;
		float m_MaxRunTime;
		float m_RunTime;
		float m_MaxBlinkTime;
		float m_BlinkTime;
	};
}