#pragma once
#include "Character.h"
#include <Collider.h>
#include <Animator.h>

namespace pacman
{
	class Ghost final : public Character
	{
		enum State
		{
			eStart = 0,
			eChase = 1,
			eRun = 2,
			eDead = 3,
			eBlink = 4,
			eRest = 5
		};

	public:
		Ghost(dae::GameObject* pGameObject);

		void Loaded() override;
		void Start() override;

		void Reset();
		void Scare();
		void Kill();

		void SetTarget(dae::GameObject* pTarget);
		void SetChaseAxis(const glm::ivec2& axis);
		void SetControlled();

		bool CanDie() const;
		bool CanKill() const;

	private:
		void SetupAnimations();
		void HandleChaseAnim();

		void EnterCWalking();
		void EnterCRun();
		void UpdateCWalking();
		void UpdateCRunning();
		void UpdateCBlinking();

		void UpdateStart();
		void UpdateDead();
		void EnterChase();
		void UpdateChase();

		void EnterRun();
		void UpdateRun();
		void EnterBlink();
		void UpdateBlink();
		void EnterRest();
		void UpdateRest();

		void UpdateDirection();
		void UpdateRunDirection();
		void UpdatePosition();
		unsigned GetRandomInt(unsigned min, unsigned max);

		glm::ivec2 m_ChaseAxis;
		Coordinate m_PrevCoordinate;
		dae::Collider* m_pCollider;
		dae::Animator* m_pAnimator;
		dae::GameObject* m_pTarget;
		float m_MaxRunTime;
		float m_RunTime;
		float m_MaxBlinkTime;
		float m_BlinkTime;
		float m_MaxRestTime;
		float m_RestTime;
		bool m_IsControlledFromOutside;

	private:
		enum AnimId
		{
			WalkX = 0,
			WalkY = 1,
			Flee = 2,
			Blinking = 3,
			Resting = 4
		};
	};
}