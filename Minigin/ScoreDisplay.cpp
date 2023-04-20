#include "ScoreDisplay.h"
#include "GameEvents.h"
#include "GameObject.h"
#include "TextRenderer.h"
#include <algorithm>

// Defining our achievements
enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};

// Achievement array which will hold data about the achievements and their state
Achievement_t g_Achievements[] =
{
	_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
	_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
	_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
	_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
};

dae::ScoreDisplay::ScoreDisplay(GameObject* gameObject)
	: dae::Component(gameObject)
	, dae::Observer()
	, m_pText{ nullptr }
	, m_Score{0}
	, m_GhostKilled{0}
	, m_SteamAchievements{nullptr}
{
	m_SteamAchievements = new CSteamAchievements(g_Achievements, 4);
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
	m_pText->SetText("Score: " + std::to_string(m_Score));

	// STEAM
	if (m_Score >= 500)
	{
		m_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
	}
}
