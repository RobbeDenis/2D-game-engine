#pragma once
#include <Component.h>
#include <TextRenderer.h>

namespace pacman
{
	class Highscore : public dae::Component
	{
	public:
		Highscore(dae::GameObject* pGameObject);

		void Loaded() override;
		void Start() override;

	private:
		void UpdateHighScore();

		dae::TextRenderer* m_pText;
	};
}