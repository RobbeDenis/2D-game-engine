#pragma once
#include <Component.h>
#include <Observer.h>
#include <vector>

namespace pacman
{
	class Ghost;
	class GameplayManager final : public dae::Component, public dae::Observer
	{
	public:
		GameplayManager(dae::GameObject* pGameObject);

		void OnNotify(Component*, unsigned) override {};
		void OnNotify(unsigned event) override;

		void AddGhost(Ghost* ghost);

	private:
		void PowerCollected();

		std::vector<Ghost*> m_pGhosts;
	};
}