#include "LivesDisplay.h"
#include "Pacman.h"
#include "PacmanEvents.h"

pacman::LivesDisplay::LivesDisplay(dae::GameObject* pGameObject)
	: Component(pGameObject)
	, Observer()
	, m_Lives{ 3 }
{

}

void pacman::LivesDisplay::Loaded()
{

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
}

int pacman::LivesDisplay::GetLives() const
{
	return m_Lives;
}
