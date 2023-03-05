#include "ETime.h"
#include <thread>

using namespace std::chrono;

dae::ETime::ETime()
	: m_DeltaTime{ 0.f }
	, m_DesiredFPS{ 300 }
	, m_DesiredMs{ 0.f }
{
	m_DesiredMs = 10000.f / m_DesiredFPS;
}

void dae::ETime::Start()
{
	m_LastTime = high_resolution_clock::now();
}

void dae::ETime::Update()
{
	m_CurruntTime = high_resolution_clock::now();
	m_DeltaTime = duration<float>(m_CurruntTime - m_LastTime).count();
	m_LastTime = m_CurruntTime;
}

void dae::ETime::Sleep()
{
	/*const float deltaMs = duration<float>(high_resolution_clock::now() - m_CurruntTime).count();

	if(deltaMs < m_DesiredMs)*/
}

void dae::ETime::SetMaxFPS(int fps)
{
	m_DesiredFPS = fps;
}

float dae::ETime::GetDeltaTime() const
{
	return m_DeltaTime;
}