#pragma once
#include "Character.h"

namespace pacman
{
	class Pacman final : public Character
	{
	public:
		Pacman(dae::GameObject* pGameObject);

		void Update() override;

	private:

	};
}