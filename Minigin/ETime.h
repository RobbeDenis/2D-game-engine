#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class ETime final : public Singleton<ETime>
	{
	public:
		ETime();

		void Start();
		void Update();
		void Sleep();

		void SetMaxFPS(int fps);
		float GetDeltaTime() const;

	private:
		std::chrono::high_resolution_clock::time_point m_CurruntTime;
		std::chrono::high_resolution_clock::time_point m_LastTime;
		float m_DeltaTime;
		std::chrono::nanoseconds m_DesiredNs;
		int m_DesiredFPS;
	};
}