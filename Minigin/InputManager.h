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
	using KeyboardCommandsMap = std::unordered_map<KeyboardInput, std::pair<std::shared_ptr<Command>, bool>, KeyboardInputHasher>;
	using ControllerCommandsMap = std::unordered_map<ControllerInput, std::shared_ptr<Command>, ControllerInputHasher>;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		bool IsPressed(unsigned button, unsigned controllerIdx = 0) const;
		bool IsReleased(unsigned button, unsigned controllerIdx = 0) const;
		bool IsDown(unsigned button, unsigned controllerIdx = 0) const;

		void SetKeyboardCommand(std::shared_ptr<KeyboardCommandsMap> map);
		void SetControllerCommand(std::shared_ptr<ControllerCommandsMap> map);

		void AddKeyboardCommand(const std::shared_ptr<KeyboardCommandsMap>& map, const KeyboardInput& input, const std::shared_ptr<Command>& command);
		void AddControllerCommand(const std::shared_ptr<ControllerCommandsMap>& map, const ControllerInput& input, const std::shared_ptr<Command>& command);

		void AddXBoxController(int controllerIndex);

	private:
		void HandleControllerInputs();
		void HandleKeyboardInputs();

		std::shared_ptr<ControllerCommandsMap> m_pControllerCommands;
		std::shared_ptr<KeyboardCommandsMap> m_pKeyboardCommands;

		std::vector<std::unique_ptr<Controller>> m_Controllers;
	};
}
