#include "ScoreDisplay.h"
#include <GameObject.h>
#include <algorithm>
#include "PacmanEvents.h"
#include "Game.h"

pacman::ScoreDisplay::ScoreDisplay(dae::GameObject* gameObject)
	: Component(gameObject)
	, Observer()
	, m_pText{ nullptr }
	, m_Score{ 0 }
	, m_GhostKilled{ 0 }
{

}

void pacman::ScoreDisplay::Loaded()
{
	m_pText = GetGameObject()->GetComponent<dae::TextRenderer>();
}

void pacman::ScoreDisplay::Start()
{
	m_Score = 0;
	m_GhostKilled = 0;
	UpdateScore();
	Game::GetInstance().SetCurrentScore(this);
}

void pacman::ScoreDisplay::OnNotify(unsigned event)
{
	switch (event)
	{
	case PEvents::CDot:
		m_Score += 10;
		UpdateScore();
		break;

	case PEvents::CPower:
		m_Score += 50;
		UpdateScore();
		break;

	case PEvents::CFruit:
		m_Score += 300;
		UpdateScore();
		break;

	case PEvents::GhostKilled:
		++m_GhostKilled;
		m_GhostKilled = std::clamp(m_GhostKilled, 0, 4);
		m_Score += static_cast<unsigned>(pow(2, m_GhostKilled)) * 100;
		UpdateScore();
		break;

	default:
		break;
	}
}

void pacman::ScoreDisplay::UpdateScore()
{
	m_pText->SetText(std::to_string(m_Score));
}