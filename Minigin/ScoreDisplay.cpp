#include "ScoreDisplay.h"
#include "GameEvents.h"
#include "GameObject.h"
#include "TextRenderer.h"
#include <algorithm>

dae::ScoreDisplay::ScoreDisplay(GameObject* gameObject)
	: dae::Component(gameObject)
	, dae::Observer()
	, m_pText{ nullptr }
	, m_Score{0}
	, m_GhostKilled{0}
{
}

void dae::ScoreDisplay::Loaded()
{
	m_pText = GetGameObject()->GetComponent<dae::TextRenderer>();
}

void dae::ScoreDisplay::OnNotify(Component*, unsigned event)
{
	switch (event)
	{
	case GameEvents::PlayerStart:
		UpdateScore();
		break;

	case GameEvents::DotCollected:
		m_Score += 10;
		UpdateScore();
		break;

	case GameEvents::EnergizerCollected:
		m_Score += 50;
		UpdateScore();
		break;

	case GameEvents::GhostKilled:
		++m_GhostKilled;
		m_GhostKilled = std::clamp(m_GhostKilled, 0, 4);
		m_Score += static_cast<unsigned>(pow(2, m_GhostKilled)) * 100;
		UpdateScore();
		break;

	case GameEvents::CherryCollected:
		m_Score += 100;
		UpdateScore();
	default:
		break;
	}
}

void dae::ScoreDisplay::UpdateScore()
{
	m_pText->SetText(std::to_string(m_Score));
}
