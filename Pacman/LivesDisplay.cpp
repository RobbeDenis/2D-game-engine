#include "LivesDisplay.h"
#include "Pacman.h"
#include "PacmanEvents.h"

pacman::LivesDisplay::LivesDisplay(dae::GameObject* pGameObject)
	: Component(pGameObject)
	, Observer()
	, m_Lives{ 0 }
	, m_MaxLives{ 3 }
{

}

void pacman::LivesDisplay::Loaded()
{

}

void pacman::LivesDisplay::Start()
{
	m_Lives = m_MaxLives;
}

void pacman::LivesDisplay::SetMaxLives(int lives)
{
	m_MaxLives = lives;
}

void pacman::LivesDisplay::OnNotify(unsigned event)
{
	switch (event)
	{
	case PEvents::PacmanDied:
		PacmanDied();
		break;
	}
}

void pacman::LivesDisplay::PacmanDied()
{
	--m_Lives;
	if (m_Lives == 0)
		Notify(PEvents::PlayerOutOffLives);
}

int pacman::LivesDisplay::GetLives() const
{
	return m_Lives;
}
