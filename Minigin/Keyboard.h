#pragma once
#include <functional>

struct KeyboardInput
{
	unsigned Key = 0;
	unsigned State = 0;

	KeyboardInput(const unsigned key, const unsigned state)
		: Key{ key }
		, State{ state } {}

	bool operator==(const KeyboardInput& other) const
	{
		return (Key == other.Key) && (State == other.State);
	}
};

struct KeyboardInputHasher
{
	size_t operator() (const KeyboardInput& data) const
	{
		size_t key = std::hash<unsigned>()(static_cast<unsigned>(data.Key));
		size_t state = std::hash<unsigned>()(static_cast<unsigned>(data.State));

		return key ^ state;
	}
};