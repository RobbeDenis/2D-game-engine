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

		virtual void Scare() = 0;

	private:
		dae::Collider* m_pCollider;
	};
}