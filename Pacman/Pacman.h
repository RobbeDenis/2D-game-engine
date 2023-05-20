#pragma once
#include "Character.h"
#include <Subject.h>

namespace pacman
{
	class Pacman final : public Character, public dae::Subject
	{
	public:
		Pacman(dae::GameObject* pGameObject);

		void Update() override;

	private:

	};
}