#pragma once
#include "InputUtils.h"
#include <iostream>
#include <string>
#include "Movement.h"
#include "TestCharacter.h"
#include <SoundSystemLocator.h>


class TestAudio : public dae::Command
{
public:
	explicit TestAudio(dae::sound_id id, float volume)
		: ID{ id } 
		, Volume{ volume } {}

	void Execute() override
	{
		dae::SoundSystemLocator::GetSoundSystem().Play(ID, Volume);
	}

private:
	dae::sound_id ID;
	float Volume;
};

class TestEvent : public dae::Command
{
public:
	explicit TestEvent(dae::TestCharacter* character, unsigned event)
		: Character{ character }
		, Event{ event } {}

	void Execute() override
	{
		Character->TestEvent(Event);
	}

private:
	dae::TestCharacter* Character;
	unsigned Event;
};


class TestKill : public dae::Command
{
public:
	explicit TestKill(dae::TestCharacter* character)
		: Character{ character } {}
		
	void Execute() override
	{
		Character->Kill();
	}

private:
	dae::TestCharacter* Character;
};

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