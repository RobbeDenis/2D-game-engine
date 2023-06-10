#pragma once
#include <Component.h>
#include <vector>
#include <string>
#include <fstream>

namespace pacman
{
	class Leaderboard : public dae::Component
	{
	public:
		Leaderboard(dae::GameObject* gameObject);

		void Loaded() override;
		void Start() override;

		void SetGamemodeId(unsigned id);
		void AddScore(unsigned score);
		void SaveScores();

	private:
		void LoadScores();

		std::vector<unsigned> m_CurrentScores;
		unsigned m_GamemodeId;

		std::ofstream m_Output;
		std::ifstream m_Input;

		template <typename T>
		void WritePod(const T& pod)
		{
			static_assert(std::is_trivially_copyable<T>::value, "T is not a POD");
			m_Output.write((char*)&pod, sizeof(T));
		}

		template<typename T>
		void ReadPod(T& pod)
		{
			static_assert(std::is_trivially_copyable<T>::value, "T is not a POD");
			m_Input.read((char*)&pod, sizeof(T));
		}

		void WriteSizeString(const std::string& s)
		{
			unsigned int size = static_cast<unsigned int>(s.size());
			m_Output.write((char*)&size, sizeof(size));
			m_Output.write(s.c_str(), size);
		}
	};
}