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

		void HandleCollisions();

		dae::Collider* m_pCollider;
	};
}