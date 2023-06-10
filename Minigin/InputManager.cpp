#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>
#include <stdexcept>
#include "XBox360Controller.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	HandleKeyboardInputs();
	HandleControllerInputs();

	return true;
}

bool dae::InputManager::IsPressed(unsigned button, unsigned controllerIdx) const
{
	if (m_Controllers.empty() || m_Controllers.size() <= controllerIdx)
		return false;

	return m_Controllers[controllerIdx]->IsPressed(button);
}

bool dae::InputManager::IsReleased(unsigned button, unsigned controllerIdx) const
{
	if (m_Controllers.empty() || m_Controllers.size() <= controllerIdx)
		return false;

	return m_Controllers[controllerIdx]->IsReleased(button);
}

bool dae::InputManager::IsDown(unsigned button, unsigned controllerIdx) const
{
	if (m_Controllers.empty() || m_Controllers.size() <= controllerIdx)
		return false;

	return m_Controllers[controllerIdx]->IsDown(button);
}

void dae::InputManager::SetKeyboardCommand(std::shared_ptr<KeyboardCommandsMap> map)
{
	if (map.get() == nullptr)
	{
		m_pKeyboardCommands.reset();
		return;
	}

	m_pKeyboardCommands = std::move(map);
}

void dae::InputManager::SetControllerCommand(std::shared_ptr<ControllerCommandsMap> map)
{
	if (map.get() == nullptr)
	{
		m_pControllerCommands.reset();
		return;
	}

	m_pControllerCommands = std::move(map);
}

void dae::InputManager::AddKeyboardCommand(const std::shared_ptr<KeyboardCommandsMap>& map, const KeyboardInput& input, const std::shared_ptr<Command>& command)
{
	if (command.get() == nullptr)
		throw std::runtime_error("Given command was nullptr");

	std::pair<std::shared_ptr<Command>, bool> pair = { command, false };
	map->emplace(input, std::move(pair));
}

void dae::InputManager::AddControllerCommand(const std::shared_ptr<ControllerCommandsMap>& map, const ControllerInput& input, const std::shared_ptr<Command>& command)
{
	if (command.get() == nullptr)
		throw std::runtime_error("Given command was nullptr");

	map->emplace(input, command);
}

void dae::InputManager::AddXBoxController(int controllerIndex)
{
	m_Controllers.push_back(std::make_unique<xbox::XBox360Controller>(controllerIndex));
}

void dae::InputManager::HandleControllerInputs()
{
	if (m_pControllerCommands.get() == nullptr)
		return;

	for (const std::unique_ptr<Controller>& controller : m_Controllers)
	{
		controller->ProcessInput();

		for (const auto& command : *m_pControllerCommands)
		{
			switch (command.first.State)
			{
			case ButtonState::Pressed:
				if (controller->IsPressed(command.first.Button))
					command.second->Execute();
				break;

			case ButtonState::Released:
				if (controller->IsReleased(command.first.Button))
					command.second->Execute();
				break;

			case ButtonState::Down:
				if (controller->IsDown(command.first.Button))
					command.second->Execute();
				break;
			}
		}
	}
}

void dae::InputManager::HandleKeyboardInputs()
{
	if (m_pKeyboardCommands.get() == nullptr)
		return;

	const Uint8* state = SDL_GetKeyboardState(NULL);

	for (auto& command : *m_pKeyboardCommands)
	{
		bool currentState = state[command.first.Key];

		switch (command.first.State)
		{
			case ButtonState::Pressed:
			{
				if (currentState && !command.second.second)
					command.second.first->Execute();
				break;
			}
			case ButtonState::Released:
			{
				if (!currentState && command.second.second)
					command.second.first->Execute();
				break;
			}
			case ButtonState::Down:
			{
				if (currentState && command.second.second)
					command.second.first->Execute();
				break;
			}
		}

		command.second.second = currentState;
	}
}
