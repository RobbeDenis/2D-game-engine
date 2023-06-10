#include "Game.h"
#include "SceneManager.h"
#include "ScoreDisplay.h"
#include <GameObject.h>
#include "SceneIds.h"
#include "Leaderboard.h"

pacman::Game::Game()
	: m_pScore{nullptr}
	, m_pLeaderboard{nullptr}
{
}

void pacman::Game::SetCurrentScore(ScoreDisplay* score)
{
	m_pScore = score;
}

void pacman::Game::SetLeaderboard(Leaderboard* board)
{
	m_pLeaderboard = board;
}

void pacman::Game::SetScene(unsigned id)
{
	auto& sm{ dae::SceneManager::GetInstance() };
	sm.SetScene(id);
}

void pacman::Game::EndGamemode()
{
	m_pLeaderboard->SetGamemodeId(m_pScore->GetGameObject()->GetScene()->GetId());
	m_pLeaderboard->AddScore(m_pScore->GetScore());
	SetScene(SceneId::Leaderboard);
}
