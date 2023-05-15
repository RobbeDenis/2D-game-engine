#pragma once
#include <InputUtils.h>
#include "Character.h"

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