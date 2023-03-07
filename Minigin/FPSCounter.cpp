#include "FPSCounter.h"
#include "TextRenderer.h"
#include "ETime.h"

dae::FPSCounter::FPSCounter(GameObject* pGameObject)
	: dae::Component(pGameObject)
	, m_UpdateInterval{ 0.6f }
	, m_CurruntUpdateInterval{ 0.f }
{

}

void dae::FPSCounter::Loaded()
{
	m_pText = m_pGameObject->GetComponent<dae::TextRenderer>();
}

void dae::FPSCounter::Start()
{
	m_pText.lock()->SetText("0 FPS");
}

void dae::FPSCounter::Update()
{
	float deltaTime = ETime::GetInstance().GetDeltaTime();

	m_CurruntUpdateInterval += deltaTime;
	if (m_CurruntUpdateInterval >= m_UpdateInterval)
	{
		int fps = int(1 / deltaTime);
		m_pText.lock()->SetText(std::to_string(fps) + " FPS");
		m_CurruntUpdateInterval = 0.f;
	}
}

void dae::FPSCounter::SetUpdateInterval(float interval)
{
	m_UpdateInterval = interval;
}
