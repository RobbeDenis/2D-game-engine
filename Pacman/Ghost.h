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

		virtual void Scare() {};
		virtual bool CanKill() const { return false; };
		virtual void Kill() {};

	private:
		dae::Collider* m_pCollider;
	};
}