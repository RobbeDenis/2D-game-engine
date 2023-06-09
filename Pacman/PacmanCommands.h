#pragma once
#include <InputUtils.h>
#include "Character.h"
#include "Gamemode.h"

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
		: m_pGamemode{gm}{}

	void Execute() override
	{
		m_pGamemode->SkipLevel();
	}

private:
	pacman::Gamemode* m_pGamemode;
};