#pragma once
#include <InputUtils.h>
#include "Character.h"
#include "Gamemode.h"
#include "Selector.h"
#include "Game.h"
#include "TypeName.h"
#include <SDLSoundSystem.h>
#include "PacmanSounds.h"

namespace commands
{
	class MoveCharacter : public dae::Command
	{
	public:
		explicit MoveCharacter(int x, int y, pacman::Character* c)
			: XDirection{ x }
			, YDirection{ y }
			, Character{ c } {}

		void Execute() override
		{
			Character->Move(XDirection, YDirection);
		}

	private:
		pacman::Character* Character;
		int XDirection = 0;
		int YDirection = 0;
	};

	class SkipLevel : public dae::Command
	{
	public:
		explicit SkipLevel(pacman::Gamemode* gm)
			: m_pGamemode{ gm } {}

		void Execute() override
		{
			m_pGamemode->SkipLevel();
		}

	private:
		pacman::Gamemode* m_pGamemode;
	};

	class MoveSelector : public dae::Command
	{
	public:
		explicit MoveSelector(pacman::Selector* s, int direction)
			: m_pSelector{ s }
			, m_Direction{ direction } {}

		void Execute() override
		{
			dae::SoundSystemLocator::GetSoundSystem().Play(PacmanSounds::Click2, 0.9f);
			m_pSelector->Move(m_Direction);
		}

	private:
		pacman::Selector* m_pSelector;
		int m_Direction;
	};

	class ConfirmSelector : public dae::Command
	{
	public:
		explicit ConfirmSelector(pacman::Selector* s)
			: m_pSelector{ s } {}

		void Execute() override
		{
			dae::SoundSystemLocator::GetSoundSystem().Play(PacmanSounds::Press, 0.6f);
			m_pSelector->Select();
		}

	private:
		pacman::Selector* m_pSelector;
	};

	class SetScene : public dae::Command
	{
	public:
		explicit SetScene(unsigned id)
			: m_Id{ id } {}

		void Execute() override
		{
			dae::SoundSystemLocator::GetSoundSystem().Play(PacmanSounds::Press, 0.6f);
			pacman::Game::GetInstance().SetScene(m_Id);
		}

	private:
		unsigned m_Id;
	};

	class QuitApplication : public dae::Command
	{
	public:
		QuitApplication() = default;

		void Execute() override
		{
			std::cout << "Command quit application\n";
			SDL_Event quitEvent{ SDL_QUIT };
			SDL_PushEvent(&quitEvent);
		}
	};

	class KillPacman : public dae::Command
	{
	public:
		explicit KillPacman(pacman::Pacman* p)
			: Player{ p } {}

		void Execute() override
		{
			Player->Kill();
		}

	private:
		pacman::Pacman* Player;
	};

	class ChangeNameIndex : public dae::Command
	{
	public:
		explicit ChangeNameIndex(pacman::TypeName* name, int dir)
			: Name{ name }
			, Direction{ dir } {}

		void Execute() override
		{
			dae::SoundSystemLocator::GetSoundSystem().Play(PacmanSounds::Click1, 0.9f);
			Name->MoveIndex(Direction);
		}

	private:
		pacman::TypeName* Name;
		int Direction;
	};

	class ChangeNameCharacter : public dae::Command
	{
	public:
		explicit ChangeNameCharacter(pacman::TypeName* name, char offset)
			: Name{ name }
			, Offset{ offset } {}

		void Execute() override
		{
			dae::SoundSystemLocator::GetSoundSystem().Play(PacmanSounds::Click2, 0.9f);
			Name->ChangeCharacter(Offset);
		}

	private:
		pacman::TypeName* Name;
		char Offset;
	};

	class ConfirmName : public dae::Command
	{
	public:
		explicit ConfirmName(pacman::TypeName* name)
			: Name{ name } {}

		void Execute() override
		{
			dae::SoundSystemLocator::GetSoundSystem().Play(PacmanSounds::Press, 0.6f);
			Name->ConfirmName();
		}

	private:
		pacman::TypeName* Name;
	};
}
