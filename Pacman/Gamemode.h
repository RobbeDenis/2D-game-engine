#pragma once
#include <Component.h>
#include <Observer.h>
#include <Subject.h>
#include <vector>
#include "Grid.h"

namespace pacman
{
	class Ghost;
	class Gamemode : public dae::Component, public dae::Observer, public dae::Subject
	{
	public:
		Gamemode(dae::GameObject* pGameObject);
		virtual ~Gamemode() = default;

		void Start() override;

		virtual void OnNotify(Component*, unsigned) override {};
		virtual void OnNotify(unsigned event) override;

		void AddGhost(Ghost* ghost);
		void AssignGrid(Grid* grid);
		virtual void SkipLevel() {};

	protected:
		void LoadLevel(unsigned level);

		std::vector<Ghost*> m_pGhosts;
		unsigned m_Level;

	private:
		void PowerCollected();

		Grid* m_pGrid;
	};
}