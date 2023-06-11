#include "Highscore.h"
#include <GameObject.h>
#include "Scene.h"
#include "Leaderboard.h"

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
	const unsigned id{ GetGameObject()->GetScene()->GetId() };
	m_pText->SetText(std::to_string(Leaderboard::GetHighscore(id)));
}
