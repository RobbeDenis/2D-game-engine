#include "Highscore.h"
#include <GameObject.h>
#include "Scene.h"

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
	std::cout << "id: " << GetGameObject()->GetScene()->GetId() << " highscore: " << "\n";
	m_pText->SetText("15310");
}
