#pragma once

namespace dae
{
	enum ButtonState
	{
		Pressed,
		Released,
		Down
	};

	class Command
	{
	public:
		Command() = default;
		virtual ~Command() {};
		virtual void Execute() = 0;
	};
}