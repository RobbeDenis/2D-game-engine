#pragma once
#include "Character.h"
#include <Collider.h>

namespace pacman
{
	class Ghost : public Character
	{
	public:
		Ghost(dae::GameObject* pGameObject);
		void Loaded() override;

	private:
		dae::Collider* m_pCollider;
	};
}