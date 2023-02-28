#include "ETime.h"

using namespace std::chrono;

dae::ETime::ETime()
	: m_DeltaTime{ 0.f }
{
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

float dae::ETime::GetDeltaTime() const
{
	return m_DeltaTime;
}