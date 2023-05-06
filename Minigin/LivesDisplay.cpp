#include "LivesDisplay.h"
#include <GameObject.h>
#include <TextRenderer.h>
#include "GameEvents.h"
#include "TestCharacter.h"

dae::LivesDisplay::LivesDisplay(GameObject* gameObject)
	: dae::Component(gameObject)
	, dae::Observer()
	, m_pText{ nullptr }
{

}

void dae::LivesDisplay::Loaded()
{
	m_pText = GetGameObject()->GetComponent<dae::TextRenderer>();
}

void dae::LivesDisplay::OnNotify(Component* component, unsigned event)
{
	TestCharacter* character = static_cast<TestCharacter*>(component);

	switch (event)
	{
		case GameEvents::PlayerStart:
		case GameEvents::PlayerDied:
		{
			std::string text{ "Lives: " + std::to_string(character->GetLives()) };
			m_pText->SetText(text);
			break;
		}
		case GameEvents::PlayerOutOffLives:
		default:
			break;
	}
}
