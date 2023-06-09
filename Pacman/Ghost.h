#pragma once
#include "Character.h"
#include <Collider.h>

namespace pacman
{
	class Ghost final : public Character
	{
		enum State
		{
			Start = 0,
			Chase = 1,
			Run = 2,
			Dead = 3,
			Blink = 4
		};

	public:
		Ghost(dae::GameObject* pGameObject);
		void Loaded() override;

		void Reset();
		void Scare();
		void Kill();

		void SetTarget(dae::GameObject* pTarget);
		void SetChaseAxis(const glm::ivec2& axis);

		bool CanDie() const;

	private:

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
		void UpdatePosition();
		unsigned GetRandomInt(unsigned min, unsigned max);

		glm::ivec2 m_ChaseAxis;
		Coordinate m_PrevCoordinate;
		dae::Collider* m_pCollider;
		dae::GameObject* m_pTarget;
		float m_MaxRunTime;
		float m_RunTime;
		float m_MaxBlinkTime;
		float m_BlinkTime;
	};
}