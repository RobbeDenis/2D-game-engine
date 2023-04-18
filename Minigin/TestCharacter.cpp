#include "TestCharacter.h"
#include <iostream>
#include "GameEvents.h"

dae::TestCharacter::TestCharacter(GameObject* gameObject)
	: dae::Component(gameObject)
	, dae::Subject()
	, m_MaxLives{ 1 }
	, m_Lives{ 1 }
{
}

void dae::TestCharacter::Start()
{
	m_Lives = m_MaxLives;
	Notify(this, GameEvents::PlayerStart);
}

void dae::TestCharacter::SetMaxLives(int lives)
{
	m_MaxLives = lives;
	m_Lives = m_MaxLives;
}

void dae::TestCharacter::Kill()
{
	if (m_Lives <= 0)
		return;

	--m_Lives;
	Notify(this, GameEvents::PlayerDied);

	if (m_Lives <= 0)
	{
		Notify(this, GameEvents::PlayerOutOffLives);
	}
}

int dae::TestCharacter::GetLives() const
{
	return m_Lives;
}

void dae::TestCharacter::TestEvent(unsigned event)
{
	Notify(this, event);
}
