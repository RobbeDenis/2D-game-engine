#pragma once
#include "Character.h"
#include <Subject.h>
#include <Collider.h>
#include <Animator.h>

namespace pacman
{
	class Pacman final : public Character, public dae::Subject
	{
	public:
		Pacman(dae::GameObject* pGameObject);
		void Loaded() override;

		void Start() override;
		void Reset() override;
		void Kill();

	private:
		enum State
		{
			Walking = 0,
			Dead = 1,
			Disabled = 2
		};

		void SetupAnimations();

		void UpdateWalking();
		void HandleWalkingAnim();
		void ExitWalking();
		void EnterDead();
		void UpdateDead();
		void ExitDead();

		void handlePickups();

		dae::Collider* m_pCollider;
		dae::Animator* m_pAnimator;
		float m_MaxDeathTime;
		float m_DeathTime;
		int m_Lives;

	private:
		enum AnimId
		{
			WalkX = 0,
			WalkY = 1, 
			Die = 2
		};
	};
}