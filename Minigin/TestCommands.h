#pragma once
#include "InputUtils.h"
#include <iostream>
#include <string>
#include "Movement.h"

class TestPrint : public dae::Command
{
public:
	explicit TestPrint(const std::string& text)
		: Text{text}{}

	void Execute() override
	{
		std::cout << Text << std::endl;
	}

private:
	std::string Text;
};

class TestMove : public dae::Command
{
public:
	explicit TestMove(int x, int y, dae::Movement* movement)
		: XDirection{x}
		, YDirection{y}
		, movement{movement} {}

	void Execute() override
	{
		movement->Move(XDirection, YDirection);
	}

private:
	dae::Movement* movement;
	int XDirection = 0;
	int YDirection = 0;
};