#include "Leaderboard.h"
#include "Game.h"
#include <iostream>
#include <algorithm>

pacman::Leaderboard::Leaderboard(dae::GameObject* gameObject)
	: Component(gameObject)
	, m_GamemodeId{ 0 }
{
}

void pacman::Leaderboard::Loaded()
{
	Game::GetInstance().SetLeaderboard(this);
}

void pacman::Leaderboard::Start()
{
	LoadScores();

	for (int i{0}; i < m_CurrentScores.size(); ++i)
	{
		std::cout << i << ": " << m_CurrentScores[i] << "\n";
	}
}

void pacman::Leaderboard::SetGamemodeId(unsigned id)
{
	m_GamemodeId = id;
}

void pacman::Leaderboard::AddScore(unsigned score)
{
	LoadScores();
	m_CurrentScores.push_back(score);
	std::sort(begin(m_CurrentScores), end(m_CurrentScores), std::less<unsigned>());
	SaveScores();
}

void pacman::Leaderboard::SaveScores()
{
	const std::string file{ std::to_string(m_GamemodeId) + ".lb" };
	if (m_Output.open(file, std::ios::binary); m_Output.is_open())
	{
		WritePod(static_cast<unsigned>(m_CurrentScores.size()));

		for (unsigned score : m_CurrentScores)
		{
			WritePod(score);
		}
	}

	m_Output.close();
}

void pacman::Leaderboard::LoadScores()
{
	m_CurrentScores.clear();

	const std::string file{ std::to_string(m_GamemodeId) + ".lb" };
	if (m_Input.open(file, std::ios::binary); m_Input.is_open())
	{
		unsigned aScores;
		ReadPod(aScores);

		for (unsigned i = 0; i < aScores; ++i)
		{
			unsigned score;
			ReadPod(score);
			m_CurrentScores.push_back(score);
		}
	}

	m_Input.close();
}
