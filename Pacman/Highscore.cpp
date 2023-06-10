#include "Highscore.h"
#include <GameObject.h>

pacman::Highscore::Highscore(dae::GameObject* pGameObject)
	: Component(pGameObject)
	, m_pText{ nullptr }
{
}

void pacman::Highscore::Loaded()
{
	m_pText = GetGameObject()->GetComponent<dae::TextRenderer>();
}

void pacman::Highscore::Start()
{
	UpdateHighScore();
}

void pacman::Highscore::UpdateHighScore()
{
	m_pText->SetText("15310");
}
