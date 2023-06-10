#pragma once
#include <Component.h>
#include <vector>
#include <string>
#include <fstream>
#include <TextRenderer.h>

namespace pacman
{
	class Leaderboard : public dae::Component
	{
	public:
		Leaderboard(dae::GameObject* gameObject);

		void Loaded() override;
		void Start() override;

		void SetGamemodeId(unsigned id);
		void AddScore(unsigned score, const std::string& name);
		void SaveScores();

		static unsigned GetHighscore(unsigned id);

	private:
		void LoadScores();
		void UpdateRenders();

		std::vector<std::pair<unsigned, std::string>> m_CurrentScores;
		std::vector<dae::TextRenderer*> m_pTextRenders;
		unsigned m_MaxRenders;
		unsigned m_GamemodeId;

		static std::ofstream m_Output;
		static std::ifstream m_Input;

		template <typename T>
		static void WritePod(const T& pod)
		{
			static_assert(std::is_trivially_copyable<T>::value, "T is not a POD");
			m_Output.write((char*)&pod, sizeof(T));
		}

		template<typename T>
		static void ReadPod(T& pod)
		{
			static_assert(std::is_trivially_copyable<T>::value, "T is not a POD");
			m_Input.read((char*)&pod, sizeof(T));
		}

		static void WriteSizeString(const std::string& s)
		{
			unsigned int size = static_cast<unsigned int>(s.size());
			m_Output.write((char*)&size, sizeof(size));
			m_Output.write(s.c_str(), size);
		}

		static void ReadSizeString(std::string& s)
		{
			unsigned int size;
			m_Input.read((char*)&size, sizeof(unsigned int));
			s.resize(size);
			m_Input.read((char*)&s[0], size);
		}
	};
}