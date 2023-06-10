#include "Selector.h"
#include <GameObject.h>
#include "Game.h"

pacman::Selector::Selector(dae::GameObject* pGameObject)
	:Component(pGameObject)
	,m_Index{}
{
}

void pacman::Selector::AddIndex(const glm::ivec2 pos, unsigned id)
{
	m_Indices.push_back(std::make_pair(pos, id));
}

void pacman::Selector::SetIndex(unsigned index)
{
	m_Index = static_cast<int>(index % m_Indices.size());
	UpdatePosition();

}

void pacman::Selector::Move(int direction)
{
	m_Index += direction;

	if (m_Index < 0)
		m_Index = static_cast<int>(m_Indices.size() - 1);
	else
		m_Index = m_Index % m_Indices.size();

	UpdatePosition();
}

void pacman::Selector::Select()
{
	if (m_Indices.empty())
		return;

	auto& game{ pacman::Game::GetInstance() };
	game.SetScene(m_Indices[m_Index].second);
}

void pacman::Selector::UpdatePosition()
{
	if (m_Indices.empty())
		return;

	const glm::ivec2 pos{ m_Indices[m_Index].first };
	GetGameObject()->SetLocalPosition(pos.x, pos.y);
}
