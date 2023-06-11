#pragma once
#include "InputUtils.h"
#include <functional>

class Controller
{
public:
	virtual ~Controller() = default;

	virtual bool IsPressed(unsigned button) const = 0;
	virtual bool IsReleased(unsigned button) const = 0;
	virtual bool IsDown(unsigned button) const = 0;

	virtual int GetIndex() const = 0;

	virtual void ProcessInput() = 0;
};

struct ControllerInput
{
	unsigned Button = 0;
	unsigned State = 0;
	int Index = 0;

	ControllerInput(unsigned button, unsigned state, int index = 0)
		: Button{ button }
		, State{ state }
		, Index{ index } { Index = Index % 4; }

	bool operator==(const ControllerInput& other) const
	{
		return (Button == other.Button) && (State == other.State) && (Index == other.Index);
	}
};

struct ControllerInputHasher
{
	std::size_t operator() (const ControllerInput& data) const
	{
		std::size_t button = std::hash<unsigned>()(static_cast<unsigned>(data.Button));
		std::size_t state = std::hash<unsigned>()(static_cast<unsigned>(data.State));

		return button ^ state;
	}
};