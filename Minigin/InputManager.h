#pragma once
#include "Singleton.h"
#include "Keyboard.h"
#include "Controller.h"
#include "InputUtils.h"
#include <unordered_map>
#include <memory>
#include <vector>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		bool IsPressed(unsigned button, unsigned controllerIdx = 0) const;
		bool IsReleased(unsigned button, unsigned controllerIdx = 0) const;
		bool IsDown(unsigned button, unsigned controllerIdx = 0) const;

		void AddKeyboardCommand(const KeyboardInput& input, const std::shared_ptr<Command>& command);
		void AddControllerCommand(const ControllerInput& input, const std::shared_ptr<Command>& command);
		void AddXBoxController(int controllerIndex);

	private:
		void HandleControllerInputs();
		void HandleKeyboardInputs();

		using KeyboardCommandsMap = std::unordered_map<KeyboardInput, std::pair<std::shared_ptr<Command>, bool>, KeyboardInputHasher>;
		using ControllerCommandsMap = std::unordered_map<ControllerInput, std::shared_ptr<Command>, ControllerInputHasher>; // Command is shared so that multiple inputs can execute the same command
		ControllerCommandsMap m_ControllerCommands;
		KeyboardCommandsMap m_KeyboardCommands;
		std::vector<std::unique_ptr<Controller>> m_Controllers;
	};
}
