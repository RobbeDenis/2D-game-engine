#include "Leaderboard.h"
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <GameObject.h>
#include "SceneIds.h"

std::ifstream pacman::Leaderboard::m_Input{ };
std::ofstream pacman::Leaderboard::m_Output{ };

pacman::Leaderboard::Leaderboard(dae::GameObject* gameObject)
	: Component(gameObject)
	, m_GamemodeId{ SceneId::Singleplayer }
	, m_MaxRenders{ 10 }
	, m_pName{ nullptr }
{
	const int offsetY{ 35 };
	for (unsigned i{ 0 }; i < m_MaxRenders; ++i)
	{
		auto go = GetGameObject()->AddChild();
		m_pTextRenders.push_back(go->AddComponent<dae::TextRenderer>());
		go->SetLocalPosition(0, static_cast<int>(i * offsetY));

		if (i == 0)
			m_pTextRenders[i]->SetColor({ 255,215,0 });
		else if (i == 1)
			m_pTextRenders[i]->SetColor({ 192,192,192 });
		else if (i == 2)
			m_pTextRenders[i]->SetColor({ 205,127,50 });
	}

	auto go = GetGameObject()->AddChild();
	m_pName = go->AddComponent<dae::TextRenderer>();
	go->SetLocalPosition(0, -60);
}

void pacman::Leaderboard::Loaded()
{
	Game::GetInstance().SetLeaderboard(this);
	LoadScores();
	UpdateRenders();
	UpdateName();
}

void pacman::Leaderboard::Start()
{
	LoadScores();
	UpdateRenders();
	UpdateName();
}

void pacman::Leaderboard::SetGamemodeId(unsigned id)
{
	m_GamemodeId = id;
}

void pacman::Leaderboard::AddScore(unsigned score, const std::string& name)
{
	LoadScores();
	m_CurrentScores.push_back(std::make_pair(score, name));
	std::sort(begin(m_CurrentScores), end(m_CurrentScores), [this](const auto& score1, const auto& score2)
		{
			return score1.first > score2.first;
		});
	SaveScores();
}

void pacman::Leaderboard::SaveScores()
{
	const std::string file{ std::to_string(m_GamemodeId) + ".lb" };
	if (m_Output.open(file, std::ios::binary); m_Output.is_open())
	{
		WritePod(static_cast<unsigned>(m_CurrentScores.size()));

		for (auto& score : m_CurrentScores)
		{
			WritePod(score.first);
			WriteSizeString(score.second);
		}
	}

	m_Output.close();
}

unsigned pacman::Leaderboard::GetHighscore(unsigned id)
{
	const std::string file{ std::to_string(id) + ".lb" };
	std::vector<unsigned> scores;

	if (m_Input.open(file, std::ios::binary); m_Input.is_open())
	{
		unsigned aScores;
		ReadPod(aScores);

		for (unsigned i = 0; i < aScores; ++i)
		{
			unsigned score;
			std::string name;
			ReadPod(score);
			ReadSizeString(name);

			scores.push_back(score);
		}
	}

	m_Input.close();

	if (scores.empty())
		return 0;

	return *std::max_element(begin(scores), end(scores));
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
			std::string name;

			ReadPod(score);
			ReadSizeString(name);

			m_CurrentScores.push_back(std::make_pair(score, name));
		}
	}

	m_Input.close();
}

void pacman::Leaderboard::UpdateRenders()
{
	for (unsigned i{ 0 }; i < m_MaxRenders; ++i)
	{
		if (i < m_CurrentScores.size())
			m_pTextRenders[i]->SetText(std::to_string(i + 1) + ". " + m_CurrentScores[i].second + ": " + std::to_string(m_CurrentScores[i].first));
		else
			m_pTextRenders[i]->SetText(" ");
	}
}

void pacman::Leaderboard::UpdateName()
{
	switch (m_GamemodeId)
	{
	case Singleplayer:
		m_pName->SetText("Singleplayer");
		break;
	case Coop:
		m_pName->SetText("Co-op");
		break;
	case Versus:
		m_pName->SetText("Versus");
		break;
	default:
		m_pName->SetText(" ");
		break;
	}
}
