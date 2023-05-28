#pragma once
#include <Component.h>
#include <Observer.h>

namespace pacman
{
	class LivesDisplay : public dae::Component, public dae::Observer
	{
	public:
		LivesDisplay(dae::GameObject* gameObject);

		void Loaded() override;
		int GetLives() const;

		void OnNotify(Component*, unsigned) override {};
		void OnNotify(unsigned event) override;

	private:
		void PacmanDied();

		int m_Lives;
	};
}