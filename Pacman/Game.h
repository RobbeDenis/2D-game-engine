#pragma once
#include <Singleton.h>
#include <InputManager.h>
#include <string>

namespace pacman
{
	class ScoreDisplay;
	class Leaderboard;
	class Game final : public dae::Singleton<Game>
	{
	public:
		Game();
		~Game() = default;

		void SetCurrentScore(ScoreDisplay* score);
		void SetLeaderboard(Leaderboard* board);
		void SetScene(unsigned id);
		void EndGamemode();
		void EnterName(const std::string& name);

	private:
		ScoreDisplay* m_pScore;
		Leaderboard* m_pLeaderboard;
	};
}