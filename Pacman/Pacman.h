#pragma once
#include "Character.h"
#include <Subject.h>
#include <Collider.h>

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
			Energized = 2
		};

		void UpdateWalking();
		void ExitWalking();
		void EnterDead();
		void UpdateDead();
		void ExitDead();

		void handlePickups();

		dae::Collider* m_pCollider;
		float m_MaxDeathTime;
		float m_DeathTime;
	};
}