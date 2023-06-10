#pragma once
#include <Singleton.h>
#include <InputManager.h>


namespace pacman
{
	class Game final : public dae::Singleton<Game>
	{
	public:
		Game();
		~Game() = default;

		void SetScene(unsigned id);

	private:
	};
}