#include "ETime.h"
#include <thread>
#include <iostream>

dae::ETime::ETime()
	: m_DeltaTime{ 0.f }
	, m_DesiredFPS{ 60 }
{
	m_DesiredNs = std::chrono::nanoseconds(1'000'000'000 / m_DesiredFPS);
}

void dae::ETime::Start()
{
	m_LastTime = std::chrono::high_resolution_clock::now();
}

void dae::ETime::Update()
{
	using namespace std::chrono;
	m_CurruntTime = high_resolution_clock::now();
	m_DeltaTime = duration<float>(m_CurruntTime - m_LastTime).count();
	m_LastTime = m_CurruntTime;
}

void dae::ETime::Sleep()
{
	std::this_thread::sleep_until(m_CurruntTime + m_DesiredNs); // Still inaccurate at high fps even after using nano seconds
}

void dae::ETime::SetMaxFPS(int fps)
{
	m_DesiredFPS = fps;
}

float dae::ETime::GetDeltaTime() const
{
	return m_DeltaTime;
}