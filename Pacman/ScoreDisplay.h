#pragma once
#include <Component.h>
#include <Observer.h>
#include <TextRenderer.h>


namespace pacman
{
	class ScoreDisplay : public dae::Component, public dae::Observer
	{
	public:
		ScoreDisplay(dae::GameObject* gameObject);

		void Loaded() override;
		void Start() override;

		void OnNotify(Component*, unsigned) override { };
		void OnNotify(unsigned event) override;

		unsigned GetScore() const { return m_Score; }

	private:
		void UpdateScore();

		dae::TextRenderer* m_pText;
		unsigned m_Score;
		int m_GhostKilled;
	};
}