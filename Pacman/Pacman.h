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
		void InitGridAgent(Grid* pGrid, const Coordinate& coordinate) override;

	private:
		enum State
		{
			Walking = 0,
			Dead = 1
		};

		void UpdateWalking();
		void ExitWalking();
		void EnterDead();
		void UpdateDead();
		void ExitDead();

		void HandleCollisions();
		void handlePickups();

		dae::Collider* m_pCollider;
		Coordinate m_SpawnPoint;
		float m_MaxDeathTime;
		float m_DeathTime;
	};
}