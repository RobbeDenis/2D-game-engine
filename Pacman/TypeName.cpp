#include "TypeName.h"
#include <GameObject.h>
#include "Game.h"

pacman::TypeName::TypeName(dae::GameObject* gameObject)
	: Component(gameObject)
	, m_Name{"AAA"}
	, m_MaxLength{ 3 }
	, m_pText{ nullptr }
	, m_Index{ 0 }
{
}

void pacman::TypeName::Loaded()
{
	m_pText = GetGameObject()->GetComponent<dae::TextRenderer>();
}

void pacman::TypeName::Start()
{
	m_Name = "AAA";
	m_Index = 0;
	UpdateName();
}

void pacman::TypeName::MoveIndex(int dir)
{
	m_Index += dir;

	if (m_Index < 0)
		m_Index = m_MaxLength - 1;
	else
		m_Index = m_Index % m_MaxLength;
}

void pacman::TypeName::ChangeCharacter(int offset)
{
	char c{ m_Name[m_Index] };
	
	c += static_cast<char>(offset);

	if (c < 'A')
		c = 'Z';
	else if (c > 'Z')
		c = 'A';

	m_Name[m_Index] = c;
	UpdateName();
}

void pacman::TypeName::ConfirmName()
{
	Game::GetInstance().EnterName(m_Name);
}

void pacman::TypeName::UpdateName()
{
	m_pText->SetText(m_Name);
}
