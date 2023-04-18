#include "TestCharacter.h"
#include <iostream>

dae::TestCharacter::TestCharacter(GameObject* gameObject)
	: dae::Component(gameObject)
	, m_Lives{ 1 }
{
}

void dae::TestCharacter::SetMaxLives(int lives)
{
	m_Lives = lives;
}

void dae::TestCharacter::Kill()
{
	if (m_Lives <= 0)
		return;

	--m_Lives;
	// Die
	std::cout << "Died " << m_Lives << " lives left\n";

	if (m_Lives <= 0)
	{
		// Game over
		std::cout << "Out of lives\n";
	}
}
