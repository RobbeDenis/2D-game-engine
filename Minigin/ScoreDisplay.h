#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class TextRenderer;
	class ScoreDisplay : public Component, public Observer
	{
	public:
		ScoreDisplay(GameObject* gameObject);

		void Loaded() override;

		void OnNotify(Component* component, unsigned event) override;
	private:
		void UpdateScore();

		TextRenderer* m_pText;
		unsigned m_Score;
		int m_GhostKilled;
	};
}